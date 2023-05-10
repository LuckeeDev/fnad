#ifndef MAP_HPP
#define MAP_HPP

#include <SFML/Graphics.hpp>
#include <vector>

#include "../entities/character/character.hpp"
#include "../epidemic/epidemic.hpp"

namespace fnad {
class Room;

class Map : public sf::Drawable {
 private:
  std::vector<Room> rooms;
  Character character;
  Epidemic epidemic;

  void draw(sf::RenderTarget&, sf::RenderStates) const override;
};
}  // namespace fnad

#endif