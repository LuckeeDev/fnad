#define _USE_MATH_DEFINES

#include "enemy.hpp"

#include <cmath>
#include <random>
#include <stdexcept>

#include "../character/character.hpp"

namespace fnad {
// Static data members
sf::Texture Enemy::dynamic_texture_;

// Constructors
Enemy::Enemy(Map const& map, sf::Vector2f const& position, Status const& status,
             float const& speed)
    : Entity(map, position, speed),
      status_{status},
      eng_((std::random_device())()),
      time_dist_(2.f, 4.f),
      direction_dist_(static_cast<float>(-M_PI_2), static_cast<float>(M_PI_2)),
      animation_direction_{Direction::down} {
  setTexture(&dynamic_texture_);

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

  std::uniform_real_distribution<float> theta_dist(
      0.f, static_cast<float>(M_PI * 2.));

  float const theta{theta_dist(eng_)};

  direction_ = {std::cos(theta), std::sin(theta)};

  time_limit_ = sf::seconds(time_dist_(eng_));
}

Enemy::Enemy(Map const& map, sf::Vector2f const& position, Status const& status)
    : Enemy(map, position, status, 30.f) {}

// Functions
void Enemy::loadTexture() {
  dynamic_texture_.loadFromFile("assets/skins/enemy/enemy_dynamic.png");
}

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

void Enemy::randomMove(sf::Time const& dt) {
  if (clock_.getElapsedTime().asSeconds() >= time_limit_.asSeconds()) {
    clock_.restart();

    float const delta_theta{direction_dist_(eng_)};

    auto const direction_x = direction_.x;
    auto const direction_y = direction_.y;

    direction_.x = direction_x * std::cos(delta_theta) -
                   direction_y * std::sin(delta_theta);
    direction_.y = direction_x * std::sin(delta_theta) +
                   direction_y * std::cos(delta_theta);

    time_limit_ = sf::seconds(time_dist_(eng_));
  }

  auto const ds = direction_ * speed_ * dt.asSeconds();

  safeMove(ds);

  auto const& enemy_position = getPosition();
  auto const min_distance_x = 0.5f * getSize().x + 0.1f;
  auto const min_distance_y = 0.5f * getSize().y + 0.1f;

  auto const& walls = map_ptr_->getWalls();

  for (auto const& wall : walls) {
    if (wall.contains(enemy_position + sf::Vector2f{min_distance_x, 0.f}) ||
        wall.contains(enemy_position - sf::Vector2f{min_distance_x, 0.f})) {
      direction_.x *= -1.f;
    }
    if (wall.contains(enemy_position + sf::Vector2f{0.f, min_distance_y}) ||
        wall.contains(enemy_position - sf::Vector2f{0.f, min_distance_y})) {
      direction_.y *= -1.f;
    }
  }
}

Status Enemy::getStatus() const { return status_; }

void Enemy::evolve(const sf::Time& dt, const Character& character) {
  if (character.getPosition() != getPosition()) {
    if (sees(character) && status_ == Status::infectious) {
      sf::Vector2f direction{character.getPosition() - getPosition()};
      float const norm2{direction.x * direction.x + direction.y * direction.y};
      direction_ = direction / std::sqrt(norm2);

      auto const ds = direction_ * 1.5f * speed_ * dt.asSeconds();

      safeMove(ds);
    } else if (status_ != Status::removed) {
      randomMove(dt);
    }
  }

  animate();
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

void Enemy::animate() {
  auto direction_x = direction_.x;
  auto direction_y = direction_.y;

  if (direction_x > 0.f && direction_x > direction_y) {
    animation_direction_ = Direction::right;
  } else if (direction_x < 0.f && direction_x < direction_y) {
    animation_direction_ = Direction::left;
  } else if (direction_x < 0.f && direction_x > direction_y) {
    animation_direction_ = Direction::down;
  } else {
    animation_direction_ = Direction::up;
  }

  auto dt = animation_clock_.getElapsedTime().asMilliseconds();

  int texture_position{96 * static_cast<int>(animation_direction_) +
                       16 * ((dt / 100) % 6)};

  setTextureRect({texture_position, 8, 16, 24});

  if (dt >= 600) {
    animation_clock_.restart();
  }
}
}  // namespace fnad