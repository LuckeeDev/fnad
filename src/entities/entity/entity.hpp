#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <SFML/Graphics.hpp>

#include "../../common/floor.hpp"

namespace fnad {
class Entity : public sf::RectangleShape {
 protected:
  Floor floor_;
  // Defined in pixels/second
  float speed_;

  Entity(Floor, sf::Vector2f, float);

 public:
  float getSpeed() const;
};
}  // namespace fnad

#endif