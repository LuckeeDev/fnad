#include <SFML/Graphics.hpp>
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
  // Defined in pixels/second
  float speed_;

 public:
  Enemy(Status status, Position position)
      : status_{status}, position_{position} {}
  Enemy(Status status)
      : Enemy(status, Position{sf::Vector2f{0.f, 0.f}, Floor::underground}) {}
  Enemy() : Enemy(Status::susceptible) {}

  const Status status() const;
  const Position position() const;
  const float speed() const;

  // Accept a delta time object indicating how much time has passed since the
  // last render
  void evolve(sf::Time);

  void infect();
};
}  // namespace fnad

#endif