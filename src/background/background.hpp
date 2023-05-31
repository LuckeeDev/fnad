#ifndef BACKGROUND_HPP
#define BACKGROUND_HPP

#include <SFML/Graphics.hpp>
#include <tmxlite/Map.hpp>
#include <tmxlite/Tileset.hpp>
#include <unordered_map>
#include <vector>

namespace fnad {
class Background : public sf::Drawable {
 private:
  unsigned int tile_size_{32};

  std::vector<tmx::Tileset> tilesets_;
  std::unordered_map<std::string, sf::Image> images_;
  std::unordered_map<int, sf::Texture> tiles_;

  sf::RenderTexture background_;
  sf::Sprite background_sprite_;

  /**
   * Draw a full Tiled layer to the RenderTexture background.
   *
   * @param layer a parsed Tiled layer
   */
  void drawLayerToBackground(tmx::TileLayer const &);

  void draw(sf::RenderTarget &, sf::RenderStates) const override;

 public:
  /**
   * Create a new background.
   *
   * @param map the parsed Tiled map
   */
  Background(tmx::Map const &);
};
}  // namespace fnad

#endif