#include <SFML/Graphics.hpp>
#include <vector>

#ifndef EPIDEMIC_HPP
#define EPIDEMIC_HPP

namespace fnad {
class Enemy;

class Epidemic {
 private:
  std::vector<Enemy> enemies_;

  double s_;
  double i_;
  double r_;

  double beta_;
  double gamma_;

  // Rate of how many days pass each second
  double days_per_second_;

 public:
  Epidemic(int, sf::Vector2f);

  void evolve(const sf::Time&);
};
}  // namespace fnad

#endif