#include "character.hpp"

namespace fnad {
// Constructors
Character::Character()
    : life_points_{3},
      Entity(Position{sf::Vector2f{0.f, 0.f}, Floor::underground}, 1.f) {}

void Character::move(const Direction& dir, const sf::Time& dt) {
  auto seconds = dt.asSeconds();
  auto ds = speed_ * seconds;

  switch (dir) {
    case Direction::up:
      position_.coordinates.y -= ds;
      break;
    case Direction::down:
      position_.coordinates.y += ds;
      break;
    case Direction::left:
      position_.coordinates.x -= ds;
      break;
    case Direction::right:
      position_.coordinates.x += ds;
      break;
  }
}

bool Character::checkContact(const Enemy& enemy) {
  auto enemy_rect = enemy.getGlobalBounds();

  auto is_contact = getGlobalBounds().intersects(enemy_rect);

  if (is_contact) {
    life_points_ -= 1;
  }

  return is_contact;
}
}  // namespace fnad