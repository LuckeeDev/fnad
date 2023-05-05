#include <SFML/Graphics.hpp>
#include <vector>

#include "../../character/character.hpp"
#include "../epidemic/epidemic.hpp"
#include "../room/room.hpp"

#ifndef MAP_HPP
#define MAP_HPP

namespace fnad {
class Map : public sf::Drawable {
 private:
  std::vector<Room> rooms;
  Character character;
  Epidemic epidemic;
};
}  // namespace fnad

#endif