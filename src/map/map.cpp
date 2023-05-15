#include "map.hpp"

#include <algorithm>
#include <cmath>
#include <stdexcept>
#include <tmxlite/Map.hpp>
#include <tmxlite/TileLayer.hpp>
#include <tmxlite/Tileset.hpp>
#include <vector>

namespace fnad {
void Map::drawLayerToBackground(tmx::TileLayer const& layer) {
  auto const& layer_tiles = layer.getTiles();
  auto const& tiles_count = layer_tiles.size();

  auto const& layer_size = layer.getSize();
  auto const& layer_width = static_cast<int>(layer_size.x);
  auto const& layer_height = static_cast<int>(layer_size.y);
  auto const& tile_area =
      layer_width * layer_height / static_cast<int>(tiles_count);
  auto const& tile_dimension = static_cast<int>(std::sqrt(tile_area));
  auto const& layer_columns = layer_width / tile_dimension;

  for (std::vector<tmx::TileLayer::Tile>::size_type i{}; i < tiles_count; i++) {
    auto const& tile = layer_tiles[i];
    auto const& index = static_cast<int>(i);
    auto const& tile_ID = static_cast<int>(tile.ID);

    if (tile_ID == 0) {
      continue;
    }

    if (tiles_.find(tile_ID) == tiles_.end()) {
      auto const& tileset = std::find_if(
          tilesets_.begin(), tilesets_.end(), [&tile](tmx::Tileset const& t) {
            return t.getFirstGID() <= tile.ID && t.getLastGID() >= tile.ID;
          });
      auto const& first_tile_ID = static_cast<int>(tileset->getFirstGID());

      auto const& column_count = static_cast<int>(tileset->getColumnCount());

      auto const& tile_size = tileset->getTileSize();
      auto const& tile_width = static_cast<int>(tile_size.x);
      auto const& tile_height = static_cast<int>(tile_size.y);

      auto const& x = (tile_ID - first_tile_ID) % column_count;
      auto const& y = (tile_ID - first_tile_ID - x) / column_count;

      auto const& image = images_[tileset->getName()];
      sf::Texture texture;

      texture.loadFromImage(image, sf::IntRect(x * tile_width, y * tile_height,
                                               tile_width, tile_height));

      tiles_[tile_ID] = texture;
    }

    auto const& tile_texture = tiles_[tile_ID];

    sf::Sprite tile_sprite;
    tile_sprite.setTexture(tile_texture);

    auto const& column = index % layer_columns;
    auto const& row = (index - column) / layer_columns;

    tile_sprite.setPosition(static_cast<float>(column * 32),
                            static_cast<float>(row * 32));

    background_.draw(tile_sprite);
  }
}

Map::Map(std::string const& file_name) {
  tmx::Map map;

  if (!map.load(file_name)) {
    throw std::invalid_argument("The file could not be read.");
  }

  tilesets_ = map.getTilesets();

  for (auto const& t : tilesets_) {
    sf::Image i;

    if (i.loadFromFile(t.getImagePath())) {
      images_[t.getName()] = i;
    }
  }

  auto const& layers = map.getLayers();

  auto const& object_layer = layers[0]->getLayerAs<tmx::ObjectGroup>();
  loadRooms(object_layer);

  background_.create(960, 640);
  background_.clear();

  for (auto it{layers.begin() + 1}; it < layers.end(); it++) {
    auto const& layer = (*it)->getLayerAs<tmx::TileLayer>();
    drawLayerToBackground(layer);
  }

  background_.display();

  background_sprite_.setTexture(background_.getTexture());
}

void Map::loadRooms(tmx::ObjectGroup const&){};

void Map::draw(sf::RenderTarget& target, sf::RenderStates) const {
  target.draw(background_sprite_);
};
}  // namespace fnad