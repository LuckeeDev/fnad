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
bool Enemy::sees(const Character& character) {
  auto joining_vector = character.getPosition() - getPosition();
  auto const& walls = map_ptr_->getWalls();

  auto v = joining_vector / 100.f;
  for (auto const& wall : walls) {
    for (auto i{0}; i != 100; i++) {
      auto p = static_cast<float>(i) * v;
      if (wall.contains(p)) {
        return false;
      };
    }
  }

  return true;
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