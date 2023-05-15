#ifndef MAP_HPP
#define MAP_HPP

#include <SFML/Graphics.hpp>
#include <tmxlite/ObjectGroup.hpp>
#include <tmxlite/TileLayer.hpp>
#include <tmxlite/Tileset.hpp>
#include <vector>

#include "../entities/character/character.hpp"
#include "../epidemic/epidemic.hpp"
#include "../room/room.hpp"

namespace fnad {
class Map : public sf::Drawable {
 private:
  Floor floor_;
  std::vector<Room> rooms_;
  void loadRooms(tmx::ObjectGroup const &);

  unsigned int tile_size_ = 32;
  std::vector<tmx::Tileset> tilesets_;
  std::unordered_map<std::string, sf::Image> images_;
  std::unordered_map<int, sf::Texture> tiles_;
  sf::RenderTexture background_;
  sf::Sprite background_sprite_;
  void drawLayerToBackground(tmx::TileLayer const &);

  void draw(sf::RenderTarget &, sf::RenderStates) const override;

 public:
  Map(std::string const &);
};
}  // namespace fnad

#endif