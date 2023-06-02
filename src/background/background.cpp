#include "background.hpp"

#include <tmxlite/Map.hpp>

namespace fnad {
void Background::drawLayerToBackground(
    tmx::TileLayer const& layer, std::vector<tmx::Tileset> const& tilesets) {
  auto const& layer_tiles = layer.getTiles();
  auto const& tiles_count = layer_tiles.size();

  for (std::vector<tmx::TileLayer::Tile>::size_type i{}; i < tiles_count; i++) {
    auto const& tmx_tile = layer_tiles[i];
    auto const& index = static_cast<int>(i);
    auto const& tile_ID = static_cast<int>(tmx_tile.ID);

    if (tile_ID == 0) {
      continue;
    }

    if (tiles_.find(tile_ID) == tiles_.end()) {
      auto const& tileset = std::find_if(
          tilesets.begin(), tilesets.end(), [&tmx_tile](tmx::Tileset const& t) {
            return t.getFirstGID() <= tmx_tile.ID &&
                   t.getLastGID() >= tmx_tile.ID;
          });
      auto const& first_tile_ID = static_cast<int>(tileset->getFirstGID());

      auto const& column_count = static_cast<int>(tileset->getColumnCount());

      auto const& tile_size = tileset->getTileSize();
      auto const& tile_width = static_cast<int>(tile_size.x);
      auto const& tile_height = static_cast<int>(tile_size.y);

      auto const& x = (tile_ID - first_tile_ID) % column_count;
      auto const& y = (tile_ID - first_tile_ID) / column_count;

      sf::IntRect const tile_rect{x * tile_width, y * tile_height, tile_width,
                                  tile_height};

      tiles_[tile_ID] = {tileset->getName(), tile_rect};
    }

    auto const& tile = tiles_[tile_ID];

    auto const& tileset_name = tile.tileset_name;
    auto const& tile_rect = tile.rect;

    sf::Sprite tile_sprite;

    tile_sprite.setTexture(textures_[tileset_name]);
    tile_sprite.setTextureRect(tile_rect);

    auto const& layer_size = layer.getSize();
    auto const& layer_columns = static_cast<int>(layer_size.x);
    auto const& column = index % layer_columns;
    auto const& row = index / layer_columns;

    tile_sprite.setPosition(
        static_cast<float>(column * static_cast<int>(tile_size_)),
        static_cast<float>(row * static_cast<int>(tile_size_)));

    background_.draw(tile_sprite);
  }
}

void Background::draw(sf::RenderTarget& target, sf::RenderStates) const {
  target.draw(background_sprite_);
};

Background::Background(tmx::Map const& map) {
  auto const& tilesets = map.getTilesets();

  for (auto const& t : tilesets) {
    sf::Texture texture;
    texture.loadFromFile(t.getImagePath());

    textures_[t.getName()] = texture;
  }

  auto const& layers = map.getLayers();

  // Assume tiles of the loaded map are always squares
  tile_size_ = map.getTileSize().x;

  auto const& map_tiles = map.getTileCount();
  auto const& map_width = map_tiles.x * tile_size_;
  auto const& map_height = map_tiles.y * tile_size_;

  background_.create(map_width, map_height);
  background_.clear(sf::Color::Transparent);

  for (auto it{layers.begin() + 4}; it < layers.end(); it++) {
    auto const& layer = (*it)->getLayerAs<tmx::TileLayer>();
    drawLayerToBackground(layer, tilesets);
  }

  background_.display();

  background_sprite_.setTexture(background_.getTexture());
}
}  // namespace fnad