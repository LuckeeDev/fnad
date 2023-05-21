#include "character.hpp"

#include "../../map/map.hpp"
#include "../enemy/enemy.hpp"

namespace fnad {
// Constructors
Character::Character(Map const& map, sf::Vector2f position, float speed)
    : Entity(map, position, speed), life_points_{3}, movement_{0.f, 0.f} {
  setFillColor(sf::Color::Blue);
}

Character::Character(Map const& map, sf::Vector2f position)
    : Character(map, position, 60.f) {}

// Functions
bool Character::checkContact(const Enemy& enemy) {
  if (enemy.getStatus() != Status::infectious) {
    return false;
  }

  auto const& enemy_rect = enemy.getGlobalBounds();

  auto is_contact = getGlobalBounds().intersects(enemy_rect);

  if (is_contact) {
    life_points_ -= 1;
  }

  return is_contact;
}

int Character::getLifePoints() const { return life_points_; }

void Character::resetMovement() { movement_ = sf::Vector2f{0.f, 0.f}; }

void Character::addMovement(Direction const& dir) {
  switch (dir) {
    case Direction::up:
      movement_ += sf::Vector2f{0.f, -1.f};
      break;
    case Direction::down:
      movement_ += sf::Vector2f{0.f, 1.f};
      break;
    case Direction::left:
      movement_ += sf::Vector2f{-1.f, 0.f};
      break;
    case Direction::right:
      movement_ += sf::Vector2f{1.f, 0.f};
      break;
  }
}

void Character::applyMovement(sf::Time const& dt) {
  if (movement_.x != 0.f || movement_.y != 0.f) {
    float const norm2 = std::pow(movement_.x, 2.f) + std::pow(movement_.y, 2.f);
    auto ds = (movement_ / std::sqrt(norm2)) * speed_ * dt.asSeconds();

    move(ds);

    if (isWallCollision()) {
      move(-ds);
    }
  }
}
}  // namespace fnad