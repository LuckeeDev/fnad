#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <SFML/Graphics.hpp>

#include "../../common/position.hpp"

namespace fnad {
class Entity : public sf::RectangleShape {
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