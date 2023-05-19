#include "epidemic.hpp"

#include <algorithm>
#include <cassert>
#include <cmath>
#include <random>

#include "../entities/enemy/enemy.hpp"
#include "../map/map.hpp"

namespace fnad {
void Epidemic::draw(sf::RenderTarget& target, sf::RenderStates) const {
  auto const& view_size = view_.getSize();
  auto const& view_center = view_.getCenter();
  auto const& top_left = view_center - view_size / 2.f;

  sf::FloatRect view_rect(top_left, view_size);

  for (auto const& e : enemies_) {
    if (view_rect.intersects(e.getGlobalBounds())) {
      target.draw(e);
    }
  }
}

Epidemic::Epidemic(const int s, const int i, Map const& map, sf::View& view)
    : SIR{static_cast<double>(s), static_cast<double>(i), 0.}, view_{view} {
  auto spawners = map.getSpawners();
  double total_area{};

  for (auto const& spawner : spawners) {
    total_area += static_cast<double>(spawner.getArea());
  }

  std::vector<Enemy> enemies;

  enemies.reserve(static_cast<unsigned int>(s + i));

  for (auto& spawner : spawners) {
    int spawner_s =
        static_cast<int>(static_cast<double>(s) *
                         static_cast<double>(spawner.getArea()) / total_area);
    int spawner_i =
        static_cast<int>(static_cast<double>(i) *
                         static_cast<double>(spawner.getArea()) / total_area);

    for (int j{}; j != spawner_s; j++) {
      Enemy enemy(map, spawner.getSpawnPoint(), Status::susceptible);
      enemies.push_back(enemy);
    }

    for (int j{}; j != spawner_i; j++) {
      Enemy enemy(map, spawner.getSpawnPoint(), Status::susceptible);
      enemies.push_back(enemy);
    }
  }

  int delta_s{s}, delta_i{i};

  for (auto const& enemy : enemies) {
    if (enemy.getStatus() == Status::susceptible) {
      delta_s--;
    } else {
      delta_i--;
    }
  }

  auto spawners_begin{spawners.begin()}, spawners_end{spawners.end()};

  for (auto it{spawners_begin}; delta_s > 0; it++, delta_s--) {
    Enemy enemy(map, it->getSpawnPoint(), Status::susceptible);
    enemies.push_back(enemy);
    if (it == spawners_end - 1) {
      it = spawners_begin;
    }
  }

  for (auto it{spawners_begin}; delta_i > 0; it++, delta_i--) {
    Enemy enemy(map, it->getSpawnPoint(), Status::infectious);
    enemies.push_back(enemy);
    if (it == spawners_end - 1) {
      it = spawners_begin;
    }
  }

  enemies_ = enemies;
}

std::vector<Enemy> const& Epidemic::getEnemies() const { return enemies_; }

SIR Epidemic::getSIRState() const { return {s_, i_, r_}; }

int Epidemic::count(Status const& status) const {
  auto const count = std::count_if(
      enemies_.begin(), enemies_.end(),
      [&status](Enemy const& e) { return e.getStatus() == status; });

  return static_cast<int>(count);
}

void Epidemic::evolve(const sf::Time& dt, const Character& character) {
  double const seconds = static_cast<double>(dt.asSeconds());
  double const days = seconds * days_per_second_;

  double const N = static_cast<double>(enemies_.size());

  double const new_s = s_ * (1. - days * beta_ * i_ / N);
  double const new_i = i_ * (1. + days * (beta_ * s_ / N - gamma_));
  double const new_r = r_ + days * gamma_ * i_;

  auto const e_begin = enemies_.begin();
  auto const e_end = enemies_.end();

  int const new_i_integer = static_cast<int>(std::round(new_i));
  int const i_count = count(Status::infectious);

  if (new_i_integer > i_count) {
    auto n_to_infect = new_i_integer - i_count;

    for (int i{}; i < n_to_infect; i++) {
      auto const to_infect = std::find_if(e_begin, e_end, [](Enemy e) {
        return e.getStatus() == Status::susceptible;
      });

      if (to_infect != e_end) {
        to_infect->infect();
      }
    }
  }

  int const new_r_integer = static_cast<int>(std::round(new_r));
  int const r_count = count(Status::removed);

  if (new_r_integer > r_count) {
    auto n_to_remove = new_r_integer - r_count;

    for (int i{}; i < n_to_remove; i++) {
      auto const to_remove = std::find_if(e_begin, e_end, [](Enemy e) {
        return e.getStatus() == Status::infectious;
      });

      if (to_remove != e_end) {
        to_remove->remove();
      }
    }
  }

  s_ = new_s;
  i_ = new_i;
  r_ = new_r;

  for (auto& enemy : enemies_) {
    enemy.evolve(dt, character);
  }
}
}  // namespace fnad
