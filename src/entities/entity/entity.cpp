#include "entity.hpp"

namespace fnad {
Entity::Entity(Floor floor, sf::Vector2f position, float speed)
    : sf::RectangleShape(sf::Vector2f{10.f, 10.f}),
      floor_{floor},
      speed_{speed} {
  setPosition(position);
};

Floor Entity::getFloor() const { return floor_; }
float Entity::getSpeed() const { return speed_; }
}  // namespace fnad