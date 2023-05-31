#ifndef BACKGROUND_HPP
#define BACKGROUND_HPP

#include <SFML/Graphics.hpp>
#include <tmxlite/Map.hpp>
#include <tmxlite/TileLayer.hpp>
#include <tmxlite/Tileset.hpp>
#include <unordered_map>
#include <vector>

namespace fnad {
struct Tile {
  std::string tileset_name;
  sf::IntRect rect;
};

class Background : public sf::Drawable {
 private:
  unsigned int tile_size_ = 32;
  std::unordered_map<std::string, sf::Texture> textures_;
  std::unordered_map<int, Tile> tiles_;
  sf::RenderTexture background_;
  sf::Sprite background_sprite_;
  void drawLayerToBackground(tmx::TileLayer const&,
                             std::vector<tmx::Tileset> const&);

  void draw(sf::RenderTarget&, sf::RenderStates) const override;

 public:
  Background(tmx::Map const&);
};
}  // namespace fnad

#endif