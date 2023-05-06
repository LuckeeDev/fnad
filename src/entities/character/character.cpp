#include "character.hpp"

namespace fnad {
// Constructors
Character::Character()
    : life_points_{3},
      Entity(Position{sf::Vector2f{0.f, 0.f}, Floor::underground}, 1.f) {}
}  // namespace fnad