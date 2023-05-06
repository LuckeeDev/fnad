#include "enemy.hpp"

#include <cassert>
#include <stdexcept>

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

void Enemy::evolve(const sf::Time& dt, const Character& character) {}

void Enemy::infect() {
  if (status_ != Status::susceptible) {
    throw std::logic_error(
        "infect can not be called on a non-susceptible Enemy");
  }

  status_ = Status::infectious;
}
}  // namespace fnad