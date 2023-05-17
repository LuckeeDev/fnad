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

Epidemic::Epidemic(const int s, const int i,
                   Map& map,  // TODO ridefinire il costruttore per
                              // inserire i nemici solo dentro alle stanze
                   sf::View& view)
    : SIR{static_cast<double>(s), static_cast<double>(i), 0.},
      view_{view} {  // per ora considero un solo piano
  sf::Vector2f map_bounds{
      960.f, 540.f};  // provvisorio (chiaramente così non ha senso)
  std::random_device r;
  std::default_random_engine gen(r());
  std::uniform_int_distribution floor_dist(0, 3);
  std::uniform_real_distribution<float> x_dist(0.f, map_bounds.x);
  std::uniform_real_distribution<float> y_dist(0.f, map_bounds.y);

  std::vector<Enemy> enemies;

  enemies.reserve(static_cast<unsigned int>(s + i));

  // Create susceptible enemies
  for (int j{}; j < s_; j++) {
    auto x = x_dist(gen);
    auto y = y_dist(gen);
    Enemy enemy(map, sf::Vector2f{x, y}, Status::susceptible);

    enemies.push_back(enemy);
  }

  // Create first infectious enemy
  for (int j{}; j < i_; j++) {
    auto x = x_dist(gen);
    auto y = y_dist(gen);
    Enemy enemy(map, sf::Vector2f{x, y}, Status::infectious);

    enemies.push_back(enemy);
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

void Epidemic::evolve(const sf::Time& dt) {
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
}
}  // namespace fnad
