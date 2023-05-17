#include "entity.hpp"

#include "../../map/map.hpp"

namespace fnad {
Entity::Entity(Map const& map, sf::Vector2f position, float speed)
    : sf::RectangleShape(sf::Vector2f{10.f, 10.f}),
      map_ptr_{&map},
      room_ptr_{nullptr},
      speed_{speed} {
  setPosition(position);
};

void Entity::setSpeed(float speed) { speed_ = speed; }

Room const& Entity::getRoom() const { return *room_ptr_; }

float Entity::getSpeed() const { return speed_; }
}  // namespace fnad