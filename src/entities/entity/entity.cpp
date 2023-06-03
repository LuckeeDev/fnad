#include "entity.hpp"

#include "../../map/map.hpp"

namespace fnad {
// Collision == operator

bool operator==(Collision const& a, Collision const& b) {
  return a.x == b.x && a.y == b.y;
}

// Constructors

Entity::Entity(Map const& map, sf::Vector2f const& position, float speed)
    : sf::RectangleShape{{32.f, 48.f}}, map_{map}, speed_{speed} {
  setOrigin(0.5f * getSize());
  setPosition(position);
};

// Public methods

Collision Entity::safeMove(sf::Vector2f const& ds) {
  // Move only on x axis, it's needed to check for the closest intersecting wall
  // on the x axis
  move(ds.x, 0.f);

  auto const entity_rect_x = getGlobalBounds();

  // Move back on the x axis and move along the y axis. This is needed to check
  // for the closest intersecting wall on the y axis
  move(-ds.x, ds.y);

  auto const entity_rect_y = getGlobalBounds();

  // Move again on the x axis to complete the full expected ds movement
  move(ds.x, 0.f);

  auto const& entity_position = getPosition();
  auto const& walls = map_.getWalls();

  // Initialize two iterators. They will point to the closest intersecting wall
  // on each axis
  auto wall_x = walls.end();
  auto wall_y = walls.end();

  for (auto it{walls.begin()}; it < walls.end(); it++) {
    // Find the closest wall on the x axis
    auto const intersects_x = entity_rect_x.intersects(*it);

    if (intersects_x) {
      if (wall_x == walls.end()) {
        wall_x = it;
        continue;
      }

      auto const is_closer_right = ds.x > 0.f && it->left < wall_x->left;
      auto const is_closer_left =
          ds.x < 0.f && (it->left + it->width) > (wall_x->left + it->width);
      auto const is_closer_x = is_closer_right || is_closer_left;

      if (is_closer_x) {
        wall_x = it;
        continue;
      }
    }

    // Find the closest wall on the y axis
    auto const intersects_y = entity_rect_y.intersects(*it);

    if (intersects_y) {
      if (wall_y == walls.end()) {
        wall_y = it;
        continue;
      }

      auto const is_closer_top = ds.y > 0.f && it->top < wall_y->top;
      auto const is_closer_bottom =
          ds.y < 0.f && (it->top + it->height) > (wall_y->top + it->height);
      auto const is_closer_y = is_closer_top || is_closer_bottom;

      if (is_closer_y) {
        wall_y = it;
        continue;
      }
    }
  }

  auto const& entity_size = getSize();
  sf::Vector2f correction;

  auto const collision_x = wall_x != walls.end();

  // Calculate x axis correction
  if (collision_x) {
    if (ds.x > 0.f) {
      correction.x = wall_x->left - entity_position.x - entity_size.x / 2.f;
    } else if (ds.x < 0.f) {
      correction.x = wall_x->left + wall_x->width - entity_position.x +
                     entity_size.x / 2.f;
    }
  }

  auto const collision_y = wall_y != walls.end();

  // Calculate y axis correction
  if (collision_y) {
    if (ds.y > 0.f) {
      correction.y = wall_y->top - entity_position.y - entity_size.y / 2.f;
    } else if (ds.y < 0.f) {
      correction.y = wall_y->top + wall_y->height - entity_position.y +
                     entity_size.y / 2.f;
    }
  }

  // Apply correction
  move(correction);

  // Return a Collision object indicating if a collision happened and where it
  // happened
  return Collision{collision_x, collision_y};
}

void Entity::setSpeed(float speed) { speed_ = speed; }

float Entity::getSpeed() const { return speed_; }
}  // namespace fnad