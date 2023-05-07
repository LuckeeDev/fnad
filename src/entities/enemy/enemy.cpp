#include "enemy.hpp"

#include <cmath>
#include <stdexcept>

#include "../character/character.hpp"

namespace fnad {
// Constructors
Enemy::Enemy(Status status, Floor floor, sf::Vector2f position, float speed)
    : Entity(floor, position, speed), status_{status} {};

Enemy::Enemy(Status status, Floor floor, sf::Vector2f position)
    : Enemy(status, floor, position, 1.f){};

Enemy::Enemy(Status status)
    : Enemy(status, Floor::underground, sf::Vector2f{0.f, 0.f}){};

Enemy::Enemy() : Enemy(Status::susceptible){};

// Functions
Status Enemy::getStatus() const { return status_; }

void Enemy::evolve(const sf::Time& dt, const Character& character) {
  if (floor_ == character.getFloor() &&
      character.getPosition() != getPosition() &&
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
}
}  // namespace fnad