#include "enemy.hpp"

#include <cmath>
#include <stdexcept>

#include "../character/character.hpp"

namespace fnad {
// Constructors
Enemy::Enemy(Map const& map, sf::Vector2f position, Status status, float speed)
    : Entity(map, position, speed), status_{status} {
  setFillColor(sf::Color::Green);
}

Enemy::Enemy(Map const& map, sf::Vector2f position, Status status)
    : Enemy(map, position, status, 1.f) {}

// Functions
bool Enemy::sees(const Character& character) const {
  auto enemy_position = getPosition();
  auto character_position = character.getPosition();
  auto joining_vector = character.getPosition() - getPosition();
  auto const& walls = map_ptr_->getWalls();

  bool r{};

  if (joining_vector.x != 0.f && joining_vector.y != 0.f) {
    auto m = joining_vector.y / joining_vector.x;
    auto q = enemy_position.y - m * enemy_position.x;

    r = std::any_of(
        walls.begin(), walls.end(),
        [&m, &q, &enemy_position, &character_position](Wall const& wall) {
          auto a = wall.top;
          auto b = wall.left;
          auto c = wall.top + wall.height;
          auto d = wall.left + wall.width;

          auto intersection_a_x = (a - q) / m;
          if (intersection_a_x > b && intersection_a_x < d &&
              (enemy_position.y - a) * (character_position.y - a) < 0) {
            return true;
          }

          auto intersection_b_y = m * b + q;
          if (intersection_b_y > a && intersection_b_y < c &&
              (enemy_position.x - b) * (character_position.x - b) < 0) {
            return true;
          }

          auto intersection_c_x = (c - q) / m;
          if (intersection_c_x > b && intersection_c_x < d &&
              (enemy_position.y - c) * (character_position.y - c) < 0) {
            return true;
          }

          auto intersection_d_y = m * d + q;
          if (intersection_d_y > a && intersection_d_y < c &&
              (enemy_position.x - d) * (character_position.x - d) < 0) {
            return true;
          }

          return false;
        });
  } else if (joining_vector.x == 0) {
    r = std::any_of(
        walls.begin(), walls.end(),
        [&enemy_position, &character_position](Wall const& wall) {
          auto left = wall.left;
          auto right = left + wall.width;
          auto top = wall.top;

          if (enemy_position.x > left && enemy_position.x < right &&
              (enemy_position.y - top) * (character_position.y - top) < 0) {
            return true;
          }

          return false;
        });
  } else {
    r = std::any_of(
        walls.begin(), walls.end(),
        [&enemy_position, &character_position](Wall const& wall) {
          auto top = wall.top;
          auto bottom = top + wall.height;
          auto left = wall.left;

          if (enemy_position.y > top && enemy_position.y < bottom &&
              (enemy_position.x - left) * (character_position.x - left) < 0) {
            return true;
          }

          return false;
        });
  }

  return r ? false : true;
}

Status Enemy::getStatus() const { return status_; }

void Enemy::evolve(const sf::Time& dt, const Character& character) {
  if (sees(character) && character.getPosition() != getPosition() &&
      status_ == Status::infectious) {
    sf::Vector2f direction{character.getPosition() - getPosition()};
    float norm2{direction.x * direction.x + direction.y * direction.y};
    direction /= std::sqrt(norm2);

    move(direction * speed_ * dt.asSeconds());
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