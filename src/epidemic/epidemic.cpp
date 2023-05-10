#include "epidemic.hpp"

#include <algorithm>
#include <cassert>
#include <cmath>
#include <random>

#include "../entities/enemy/enemy.hpp"

namespace fnad {
Epidemic::Epidemic(const unsigned int n, const sf::Vector2f map)
    : SIR{n - 1., 1., 0.} {
  std::random_device r;
  std::default_random_engine gen(r());
  std::uniform_int_distribution floor_dist(0, 3);
  std::uniform_real_distribution<float> x_dist(0.f, map.x);
  std::uniform_real_distribution<float> y_dist(0.f, map.y);

  std::vector<Enemy> enemies;

  enemies.reserve(n);

  // Create susceptible enemies
  for (int i{}; i < s_; i++) {
    auto floor = static_cast<Floor>(floor_dist(gen));
    auto x = x_dist(gen);
    auto y = y_dist(gen);
    Enemy enemy(Status::susceptible, floor, sf::Vector2f{x, y});

    enemies.push_back(enemy);
  }

  // Create first infectious enemy
  for (int i{}; i < i_; i++) {
    auto floor = static_cast<Floor>(floor_dist(gen));
    auto x = x_dist(gen);
    auto y = y_dist(gen);
    Enemy enemy(Status::infectious, floor, sf::Vector2f{x, y});

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
