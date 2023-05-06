#include "enemy.hpp"

namespace fnad {
// Constructors
Enemy::Enemy(Status status, Floor floor, sf::Vector2f position, float speed)
    : status_{status}, Entity(floor, position, speed){};

Enemy::Enemy(Status status, Floor floor, sf::Vector2f position)
    : Enemy(status, floor, position, 1.f){};

Enemy::Enemy(Status status)
    : Enemy(status, Floor::underground, sf::Vector2f{0.f, 0.f}){};

Enemy::Enemy() : Enemy(Status::susceptible){};

// Functions
Status Enemy::getStatus() const { return status_; }
}  // namespace fnad