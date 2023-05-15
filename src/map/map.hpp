#ifndef MAP_HPP
#define MAP_HPP

#include <SFML/Graphics.hpp>
#include <vector>

#include "../entities/character/character.hpp"
#include "../epidemic/epidemic.hpp"

// Forward declarations of tmxlite's classes
namespace tmx {
class ObjectGroup;
class TileLayer;
class Tileset;
}  // namespace tmx

namespace fnad {
class Room;

class Map : public sf::Drawable {
 private:
  std::vector<Room> rooms_;
  void loadRooms(tmx::ObjectGroup const &);

  const std::vector<tmx::Tileset> &tilesets_;
  std::unordered_map<std::string, sf::Image> images_;
  std::unordered_map<int, sf::Texture> tiles_;
  sf::RenderTexture background_;
  void drawLayerToBackground(tmx::TileLayer const &);

  void draw(sf::RenderTarget &, sf::RenderStates) const override;

 public:
  Map(std::string const &);
};
}  // namespace fnad

#endif