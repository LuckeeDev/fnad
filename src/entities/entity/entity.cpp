#include "entity.hpp"

namespace fnad {
Entity::Entity(Floor floor, sf::Vector2f position, float speed)
    : sf::RectangleShape(sf::Vector2f{10.f, 10.f}),
      floor_{floor},
      speed_{speed} {
  setPosition(position);
};

void Entity::setFloor(const Floor& floor) { floor_ = floor; }
void Entity::setSpeed(const float& speed) { speed_ = speed; }

Floor Entity::getFloor() const { return floor_; }
float Entity::getSpeed() const { return speed_; }
}  // namespace fnad