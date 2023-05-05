#include <SFML/Graphics.hpp>
#ifndef POSITION_HPP
#define POSITION_HPP

namespace fnad {
enum class Floor { underground, ground, first, second, roof };

struct Position {
  sf::Vector2f coordinates;
  Floor floor;
};
}  // namespace fnad

#endif