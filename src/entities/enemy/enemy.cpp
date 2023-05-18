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
Status Enemy::getStatus() const { return status_; }

void Enemy::evolve(const sf::Time& dt, const Character& character) {
  if (character.getPosition() != getPosition() &&
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