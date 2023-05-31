#include "entity.hpp"

#include <iostream>

#include "../../map/map.hpp"

namespace fnad {
Entity::Entity(Map const& map, sf::Vector2f const& position, float speed)
    : sf::RectangleShape({8.f, 12.f}), map_{map}, speed_{speed} {
  setOrigin(0.5f * getSize());
  setPosition(position);
};

void Entity::handleWallCollision(Axis const& axis, float const& movement) {
  auto const& position = getPosition();
  auto const& size = getSize();
  auto const& walls = map_.getWalls();
  auto const& entity_rect{getGlobalBounds()};

  auto wall = walls.end();

  for (auto it{walls.begin()}; it < walls.end(); it++) {
    auto const intersects = entity_rect.intersects(*it);

    if (intersects) {
      if (wall == walls.end()) {
        wall = it;
        continue;
      }

      auto const is_closer_right = movement > 0.f && it->left < wall->left;
      auto const is_closer_left =
          movement < 0.f && (it->left + it->width) > (wall->left + it->width);
      auto const is_closer_x = is_closer_right || is_closer_left;

      auto const is_closer_top = movement > 0.f && it->top < wall->top;
      auto const is_closer_bottom =
          movement < 0.f && (it->top + it->height) > (wall->top + it->height);
      auto const is_closer_y = is_closer_top || is_closer_bottom;

      if (axis == Axis::x && is_closer_x) {
        wall = it;
        continue;
      }

      if (axis == Axis::y && is_closer_y) {
        wall = it;
        continue;
      }
    }
  }

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