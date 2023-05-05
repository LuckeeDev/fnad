#include <SFML/Graphics.hpp>
#include <vector>

#include "../../common/position.hpp"

#ifndef ENEMY_HPP
#define ENEMY_HPP

namespace fnad {
enum class Status { susceptible, infectious, removed };

class Enemy {
 private:
  Status status_;
  Position position_;

 public:
  Enemy(Status status, Position position)
      : status_{status}, position_{position} {}
  Enemy(Status status)
      : Enemy(status, Position{sf::Vector2f{0.f, 0.f}, Floor::underground}) {}
  Enemy() : Enemy(Status::susceptible) {}

  void evolve();
};
}  // namespace fnad

#endif