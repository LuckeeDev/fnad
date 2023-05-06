#include "character.hpp"

namespace fnad {
// Constructors
Character::Character()
    : life_points_{3},
      Entity(Floor::underground, sf::Vector2f{0.f, 0.f}, 1.f) {}

void Character::move(const Direction& dir, const sf::Time& dt) {
  auto seconds = dt.asSeconds();
  auto ds = speed_ * seconds;

  switch (dir) {
    case Direction::up:
      move(0.f, -ds);
      break;
    case Direction::down:
      move(0.f, ds);
      break;
    case Direction::left:
      move(-ds, 0.f);
      break;
    case Direction::right:
      move(ds, 0.f);
      break;
  }
}

bool Character::checkContact(const Enemy& enemy) {
  if (enemy.status() == Status::susceptible ||
      enemy.status() == Status::removed) {
    return false;
  }

  auto enemy_rect = enemy.getGlobalBounds();

  auto is_contact = getGlobalBounds().intersects(enemy_rect);

  if (is_contact) {
    life_points_ -= 1;
  }

  return is_contact;
}

int Character::getLifePoints() const { return life_points_; }
}  // namespace fnad