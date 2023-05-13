#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include <string>
#include <tmxlite/Map.hpp>
#include <tmxlite/TileLayer.hpp>
#include <unordered_map>

int main() {
  sf::RenderWindow window(sf::VideoMode(960, 640), "Map test");
  window.setFramerateLimit(60);

  std::unordered_map<std::string, sf::Image> images;
  std::unordered_map<int, sf::Texture> tiles;

  sf::RenderTexture background;
  background.create(960, 640);
  background.clear();
  sf::Sprite sprite;

  tmx::Map map;
  if (map.load("assets/map/test.tmx")) {
    auto const& layers = map.getLayers();

    auto const& tilesets = map.getTilesets();

    for (auto const& t : tilesets) {
      sf::Image i;

      if (i.loadFromFile(t.getImagePath())) {
        images[t.getName()] = i;
      }
    }

    auto const& layer = layers[0]->getLayerAs<tmx::TileLayer>();
    auto const& layer_tiles = layer.getTiles();
    auto const& tiles_count = static_cast<int>(layer_tiles.size());

    auto const& layer_size = layer.getSize();
    auto const& tile_area = layer_size.x * layer_size.y / tiles_count;
    auto const& tile_dimension = static_cast<int>(std::sqrt(tile_area));
    auto const& layer_columns = layer_size.x / tile_dimension;

    for (int i{}; i < tiles_count; i++) {
      auto const& tile = layer_tiles[i];

      if (tiles.find(tile.ID) == tiles.end()) {
        auto const& tileset = std::find_if(
            tilesets.begin(), tilesets.end(), [&tile](tmx::Tileset tileset) {
              return tileset.getFirstGID() <= tile.ID &&
                     tileset.getLastGID() >= tile.ID;
            });

        auto const& image = images[tileset->getName()];

        sf::Texture texture;
        auto const& column_count = tileset->getColumnCount();
        auto const& tile_size = tileset->getTileSize();
        int const& x = (tile.ID - tileset->getFirstGID()) % column_count;
        int const& y = (tile.ID - tileset->getFirstGID() - x) / column_count;

        texture.loadFromImage(
            image, sf::IntRect(x * tile_size.x, y * tile_size.y, tile_size.x,
                               tile_size.y));

        tiles[tile.ID] = texture;
      }

      auto tile_texture = tiles[tile.ID];

      sf::Sprite tile_sprite;
      tile_sprite.setTexture(tile_texture);

      auto const& column = i % layer_columns;
      auto const& row = (i - column) / layer_columns;

      tile_sprite.setPosition(sf::Vector2f{column * 32, row * 32});

      background.draw(tile_sprite);
    }

    background.display();

    sprite.setTexture(background.getTexture());

    while (window.isOpen()) {
      sf::Event event;
      while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) window.close();
      }

      window.clear(sf::Color::Black);

      window.draw(sprite);

      window.display();
    }
  }
}