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

  if (joining_vector.x != 0.f && joining_vector.y != 0.f) {
    auto const m = joining_vector.y / joining_vector.x;
    auto const q = enemy_position.y - m * enemy_position.x;

    return std::none_of(
        walls.begin(), walls.end(),
        [&m, &q, &enemy_position, &character_position](Wall const& wall) {
          auto const& a = wall.top;
          auto const& b = wall.left;
          auto const c = wall.top + wall.height;
          auto const d = wall.left + wall.width;

          auto const intersection_a_x = (a - q) / m;
          if (intersection_a_x > b && intersection_a_x < d &&
              (enemy_position.y - a) * (character_position.y - a) < 0) {
            return true;
          }

          auto const intersection_b_y = m * b + q;
          if (intersection_b_y > a && intersection_b_y < c &&
              (enemy_position.x - b) * (character_position.x - b) < 0) {
            return true;
          }

          auto const intersection_c_x = (c - q) / m;
          if (intersection_c_x > b && intersection_c_x < d &&
              (enemy_position.y - c) * (character_position.y - c) < 0) {
            return true;
          }

          auto const intersection_d_y = m * d + q;
          if (intersection_d_y > a && intersection_d_y < c &&
              (enemy_position.x - d) * (character_position.x - d) < 0) {
            return true;
          }

          return false;
        });
  } else if (joining_vector.x == 0) {
    return std::none_of(
        walls.begin(), walls.end(),
        [&enemy_position, &character_position](Wall const& wall) {
          auto const& left = wall.left;
          auto const right = left + wall.width;
          auto const& top = wall.top;

          return enemy_position.x > left && enemy_position.x < right &&
                 (enemy_position.y - top) * (character_position.y - top) < 0;
        });
  } else {
    return std::none_of(
        walls.begin(), walls.end(),
        [&enemy_position, &character_position](Wall const& wall) {
          auto const& top = wall.top;
          auto const bottom = top + wall.height;
          auto const& left = wall.left;

          return enemy_position.y > top && enemy_position.y < bottom &&
                 (enemy_position.x - left) * (character_position.x - left) < 0;
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
  status_ = Status::removed;
  setFillColor(sf::Color::Black);
}
}  // namespace fnad