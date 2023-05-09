#include <SFML/Graphics.hpp>
#include <vector>
#include "../entities/enemy/enemy.hpp"

#ifndef EPIDEMIC_HPP
#define EPIDEMIC_HPP

namespace fnad {
//class Enemy;

class Epidemic {
 private:
  std::vector<Enemy> enemies_;

  double s_;
  double i_{1.};
  double r_{};

  double beta_{0.7};
  double gamma_{0.4};

  // Rate of how many days pass each second
  double days_per_second_{1};

 public:
  Epidemic(int, sf::Vector2f);

  std::vector<Enemy> const& getEnemies() const;
  int count(Status const&) const;

  void evolve(const sf::Time&);
};
}  // namespace fnad

#endif