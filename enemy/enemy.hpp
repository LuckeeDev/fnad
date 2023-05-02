#include <SFML/Graphics>
#include <vector>

#ifndef ENEMY_HPP
#define ENEMY_HPP

namespace fnad {
enum class Status { susceptible, infectious, removed };

enum class Floor { underground, ground, first, second, roof };

struct Position {
  sf::Vector2f coordinates;
  Floor floor;
};

class Enemy {
 private:
  Status status_;
  Position position_;

 public:
  Enemy(Status status, Position position)
      : status_{status}, position_{position} {}
  Enemy(Status status) : Enemy(status, sf::Vector2f{0.f, 0.f}) {}
  Enemy() : Enemy(Status::susceptible) {}
  void evolve();
};
}  // namespace fnad

#endif