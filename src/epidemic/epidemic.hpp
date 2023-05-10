#ifndef EPIDEMIC_HPP
#define EPIDEMIC_HPP

#include <SFML/Graphics.hpp>
#include <vector>

#include "../entities/enemy/enemy.hpp"

namespace fnad {
// class Enemy;

struct SIR {
  double s_;
  double i_;
  double r_;
};

class Epidemic : private SIR {
 private:
  std::vector<Enemy> enemies_;

  double const beta_{0.7};
  double const gamma_{0.4};

  // Rate of how many days pass each second
  double const days_per_second_{1.};

 public:
  Epidemic(const int, const int, const sf::Vector2f);

  std::vector<Enemy> const& getEnemies() const;
  SIR getSIRState() const;
  int count(Status const&) const;

  void evolve(const sf::Time&);
};
}  // namespace fnad

#endif