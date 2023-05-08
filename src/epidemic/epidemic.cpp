#include "epidemic.hpp"

#include <algorithm>
#include <cmath>

#include "../entities/enemy/enemy.hpp"

void fnad::Epidemic::evolve(const sf::Time& dt) {
  double seconds = static_cast<double>(dt.asSeconds());
  double days = seconds * days_per_second_;

  double N = static_cast<double>(enemies_.size());

  double new_s = s_ * (1. - days * beta_ * i_ / N);
  double new_i = i_ * (1. + days * (beta_ * s_ / N - gamma_));
  double new_r = r_ + days * gamma_ * i_;

  auto e_begin = enemies_.begin();
  auto e_end = enemies_.end();

  if (std::round(new_i) != std::round(i_)) {
    auto to_infect = std::find_if(e_begin, e_end, [](Enemy e) {
      return e.getStatus() == fnad::Status::susceptible;
    });

    to_infect->infect();
  }

  if (std::round(new_r) != std::round(r_)) {
    auto to_remove = std::find_if(e_begin, e_end, [](Enemy e) {
      return e.getStatus() == fnad::Status::infectious;
    });

    to_remove->remove();
  }

  s_ = new_s;
  i_ = new_i;
  r_ = new_r;
}