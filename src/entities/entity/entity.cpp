#include "entity.hpp"

#include "../../map/map.hpp"

namespace fnad {
Entity::Entity(Map const& map, sf::Vector2f position, float speed)
    : sf::RectangleShape(sf::Vector2f{10.f, 10.f}),
      map_ptr_{&map},
      speed_{speed} {
  setPosition(position);
};

bool Entity::isWallCollision() {
  auto walls = map_ptr_->getWalls();
  sf::FloatRect entity{getPosition(), getSize()};

  for (auto const& wall : walls) {
    if (entity.intersects(wall)) {
      return true;
    }
  }

  return false;
}

void Entity::setSpeed(float speed) { speed_ = speed; }

float Entity::getSpeed() const { return speed_; }
}  // namespace fnad