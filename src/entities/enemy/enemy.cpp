#include "enemy.hpp"

#include <cmath>
#include <stdexcept>

#include "../character/character.hpp"

namespace fnad {
// Constructors
Enemy::Enemy(Map const& map, sf::Vector2f position, Status status, float speed)
    : Entity(map, position, speed), status_{status} {
  switch (status) {
    case Status::susceptible:
      setFillColor(sf::Color::Green);
      break;
    case Status::infectious:
      setFillColor(sf::Color::Red);
      break;
    case Status::removed:
      setFillColor(sf::Color::Black);
      break;
  }
}

Enemy::Enemy(Map const& map, sf::Vector2f position, Status status)
    : Enemy(map, position, status, 30.f) {}

// Functions
bool Enemy::sees(const Character& character) const {
  auto const& enemy_position = getPosition();
  auto const& character_position = character.getPosition();
  auto const joining_vector = character.getPosition() - getPosition();
  auto const& walls = map_ptr_->getWalls();

  // Check general case
  if (joining_vector.x != 0.f && joining_vector.y != 0.f) {
    auto const line_slope = joining_vector.y / joining_vector.x;
    auto const line_intercept =
        enemy_position.y - line_slope * enemy_position.x;

    return std::none_of(
        walls.begin(), walls.end(),
        [&line_slope, &line_intercept, &enemy_position,
         &character_position](Wall const& wall) {
          auto const& top_side = wall.top;
          auto const& left_side = wall.left;
          auto const bottom_side = wall.top + wall.height;
          auto const right_side = wall.left + wall.width;

          auto const top_intersection =
              (top_side - line_intercept) / line_slope;
          if (top_intersection > left_side && top_intersection < right_side &&
              (enemy_position.y - top_side) *
                      (character_position.y - top_side) <
                  0) {
            return true;
          }

          auto const left_intersection =
              line_slope * left_side + line_intercept;
          if (left_intersection > top_side && left_intersection < bottom_side &&
              (enemy_position.x - left_side) *
                      (character_position.x - left_side) <
                  0) {
            return true;
          }

          auto const bottom_intersection =
              (bottom_side - line_slope) / line_intercept;
          if (bottom_intersection > left_side &&
              bottom_intersection < right_side &&
              (enemy_position.y - bottom_side) *
                      (character_position.y - bottom_side) <
                  0) {
            return true;
          }

          auto const right_intersection =
              line_slope * right_side + line_intercept;
          if (right_intersection > top_side &&
              right_intersection < bottom_side &&
              (enemy_position.x - right_side) *
                      (character_position.x - right_side) <
                  0) {
            return true;
          }

          return false;
        });
    // Check when the joining vector is parallel to the right and left sides
  } else if (joining_vector.x == 0.f) {
    return std::none_of(
        walls.begin(), walls.end(),
        [&enemy_position, &character_position](Wall const& wall) {
          auto const& left_side = wall.left;
          auto const right_side = left_side + wall.width;
          auto const& top_side = wall.top;

          return enemy_position.x > left_side &&
                 enemy_position.x < right_side &&
                 (enemy_position.y - top_side) *
                         (character_position.y - top_side) <
                     0;
        });
    // Check when the joining vector is parallel to the top and bottom sides
  } else {
    return std::none_of(
        walls.begin(), walls.end(),
        [&enemy_position, &character_position](Wall const& wall) {
          auto const& top_side = wall.top;
          auto const bottom_side = top_side + wall.height;
          auto const& left_side = wall.left;

          return enemy_position.y > top_side &&
                 enemy_position.y < bottom_side &&
                 (enemy_position.x - left_side) *
                         (character_position.x - left_side) <
                     0;
        });
  }
}

Status Enemy::getStatus() const { return status_; }

void Enemy::evolve(const sf::Time& dt, const Character& character) {
  if (sees(character) && character.getPosition() != getPosition() &&
      status_ == Status::infectious) {
    sf::Vector2f direction{character.getPosition() - getPosition()};
    float const norm2{direction.x * direction.x + direction.y * direction.y};
    direction /= std::sqrt(norm2);

    auto const ds = direction * speed_ * dt.asSeconds();

    move(ds);

    if (isWallCollision()) {
      move(-ds);
    }
  }
}

void Enemy::infect() {
  if (status_ != Status::susceptible) {
    throw std::logic_error(
        "infect can not be called on a non-susceptible Enemy");
  }

  status_ = Status::infectious;
  setFillColor(sf::Color::Red);
}

void Enemy::remove() {
  if (status_ != Status::infectious) {
    throw std::logic_error(
        "remove can not be called on a non-infectious Enemy");
  }

  status_ = Status::removed;
  setFillColor(sf::Color::Black);
}
}  // namespace fnad