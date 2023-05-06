#include "entity.hpp"

namespace fnad {
Entity::Entity(Floor floor, sf::Vector2f position, float speed)
    : floor_{floor},
      speed_{speed},
      sf::RectangleShape(sf::Vector2f{10.f, 10.f}) {
  setPosition(position);
};

float Entity::getSpeed() const { return speed_; }
}  // namespace fnad