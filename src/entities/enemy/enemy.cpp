#include "enemy.hpp"

namespace fnad {
// Constructors
Enemy::Enemy(Status status, Position position, float speed)
    : status_{status}, Entity(position, speed){};

Enemy::Enemy(Status status, Position position) : Enemy(status, position, 1.f){};

Enemy::Enemy(Status status)
    : Enemy(status, Position{sf::Vector2f{0.f, 0.f}, Floor::underground}){};

Enemy::Enemy() : Enemy(Status::susceptible){};
}  // namespace fnad