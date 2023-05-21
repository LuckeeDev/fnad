#include "entity.hpp"

#include <iostream>

#include "../../map/map.hpp"

namespace fnad {
Entity::Entity(Map const& map, sf::Vector2f position, float speed)
    : sf::RectangleShape(sf::Vector2f{10.f, 10.f}),
      map_ptr_{&map},
      speed_{speed} {
  setOrigin(5.f, 5.f);
  setPosition(position);
};

void Entity::handleWallCollision(Axis const& axis, float const& movement) {
  auto const& position = getPosition();
  auto const& size = getSize();
  auto const& walls = map_ptr_->getWalls();
  sf::FloatRect const& entity_rect{getGlobalBounds()};

  auto const wall = std::find_if(
      walls.begin(), walls.end(),
      [&entity_rect](Wall const& w) { return entity_rect.intersects(w); });

  if (wall != walls.end()) {
    // Handle horizontal collision
    if (axis == Axis::x) {
      float correction{};

      if (movement > 0.f) {
        correction = wall->left - position.x - size.x / 2.f;
      } else if (movement < 0.f) {
        correction = wall->left + wall->width - position.x + size.x / 2.f;
      }

      move(correction, 0.f);
    }

    // Handle vertical collision
    if (axis == Axis::y) {
      float correction{};

      if (movement > 0.f) {
        correction = wall->top - position.y - size.y / 2.f;
      } else if (movement < 0.f) {
        correction = wall->top + wall->height - position.y + size.y / 2.f;
      }

      move(0.f, correction);
    }
  }
}

void Entity::safeMove(sf::Vector2f const& ds) {
  if (ds.x != 0.f) {
    move(ds.x, 0.f);

    handleWallCollision(Axis::x, ds.x);
  }

  // Handle vertical movement
  if (ds.y != 0.f) {
    move(0.f, ds.y);

    handleWallCollision(Axis::y, ds.y);
  }
}

void Entity::setSpeed(float speed) { speed_ = speed; }

float Entity::getSpeed() const { return speed_; }
}  // namespace fnad