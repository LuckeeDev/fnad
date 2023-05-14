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
  std::vector<Room> rooms_;
  void loadRooms(tmx::ObjectGroup const&);

  sf::RenderTexture background;
  void loadBackground(tmx::TileLayer const&);

  void draw(sf::RenderTarget&, sf::RenderStates) const override;

 public:
  bool loadMap(std::string const&);
};
}  // namespace fnad

#endif