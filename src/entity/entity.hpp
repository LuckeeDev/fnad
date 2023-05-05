#include <SFML/Graphics.hpp>

#ifndef ENTITY_HPP
#define ENTITY_HPP

namespace fnad {
enum class Floor { underground, ground, first, second, roof };

struct Position {
  sf::Vector2f coordinates;
  Floor floor;
};

class Entity {
 protected:
  Position position_;
  // Defined in pixels/second
  float speed_;

  Entity(Position position, float speed);

 public:
  Position position() const;
  float speed() const;
};
}  // namespace fnad

#endif