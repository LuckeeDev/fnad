#include "entity.hpp"

#include "../../map/map.hpp"

namespace fnad {
Entity::Entity(Map const& map, sf::Vector2f position, float speed)
    : sf::RectangleShape(sf::Vector2f{10.f, 10.f}),
      map_ptr_{&map},
      speed_{speed} {
  setOrigin(5.f, 5.f);
  setPosition(position);
};

bool Entity::isWallCollision() const {
  auto const& walls = map_ptr_->getWalls();
  sf::FloatRect entity{getGlobalBounds()};

  if (std::any_of(walls.begin(), walls.end(),
                  [entity](Wall wall) { return entity.intersects(wall); })) {
    return true;
  }

  return false;
}

void Entity::setSpeed(float speed) { speed_ = speed; }

float Entity::getSpeed() const { return speed_; }
}  // namespace fnad