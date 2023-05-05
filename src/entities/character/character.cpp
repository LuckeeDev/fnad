#include "character.hpp"

namespace fnad {
// Constructors
Character::Character()
    : life_points_{3}, position_{sf::Vector2f{0.f, 0.f}, Floor::underground} {}
}  // namespace fnad