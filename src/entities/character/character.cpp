#include "character.hpp"

#include "../enemy/enemy.hpp"
#include "../../map/map.hpp"

namespace fnad {
// Constructors
Character::Character(Map& map, sf::Vector2f position)
    : Entity(map, position, 1.f),
      life_points_{3} {}

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
  if (enemy.getFloor() != floor_ || enemy.getStatus() != Status::infectious) {
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