#ifndef POSITION_HPP
#define POSITION_HPP

#include <SFML/Graphics.hpp>

namespace fnad {
enum class Floor { underground, ground, first, second, roof };

struct Position {
  sf::Vector2f coordinates;
  Floor floor;
};
}  // namespace fnad

#endif