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

  sf::View view(sf::Vector2f(100.f, 100.f), sf::Vector2f(300.f, 200.f));
  window.setView(view);

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
    auto const& tiles_count = layer_tiles.size();

    auto const& layer_size = layer.getSize();
    auto const& layer_width = static_cast<int>(layer_size.x);
    auto const& layer_height = static_cast<int>(layer_size.y);
    auto const& tile_area =
        layer_width * layer_height / static_cast<int>(tiles_count);
    auto const& tile_dimension = static_cast<int>(std::sqrt(tile_area));
    auto const& layer_columns = layer_width / tile_dimension;

    for (std::vector<tmx::TileLayer::Tile>::size_type i{}; i < tiles_count;
         i++) {
      auto const& tile = layer_tiles[i];
      auto const& index = static_cast<int>(i);
      auto const& tile_ID = static_cast<int>(tile.ID);

      if (tiles.find(tile_ID) == tiles.end()) {
        auto const& tileset = std::find_if(
            tilesets.begin(), tilesets.end(), [&tile](tmx::Tileset const& t) {
              return t.getFirstGID() <= tile.ID && t.getLastGID() >= tile.ID;
            });
        auto const& first_tile_ID = static_cast<int>(tileset->getFirstGID());

        auto const& column_count = static_cast<int>(tileset->getColumnCount());

        auto const& tile_size = tileset->getTileSize();
        auto const& tile_width = static_cast<int>(tile_size.x);
        auto const& tile_height = static_cast<int>(tile_size.y);

        int const& x = (tile_ID - first_tile_ID) % column_count;
        int const& y = (tile_ID - first_tile_ID - x) / column_count;

        auto const& image = images[tileset->getName()];
        sf::Texture texture;

        texture.loadFromImage(
            image, sf::IntRect(x * tile_width, y * tile_height, tile_width,
                               tile_height));

        tiles[tile_ID] = texture;
      }

      auto tile_texture = tiles[tile_ID];

      sf::Sprite tile_sprite;
      tile_sprite.setTexture(tile_texture);

      auto const& column = index % layer_columns;
      auto const& row = (index - column) / layer_columns;

      tile_sprite.setPosition(static_cast<float>(column * 32),
                              static_cast<float>(row * 32));

      background.draw(tile_sprite);
    }

    background.display();

    sprite.setTexture(background.getTexture());

    while (window.isOpen()) {
      sf::Event event;
      while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) window.close();

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
          view.move(-10.f, 0.f);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
          view.move(10.f, 0.f);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
          view.move(0.f, -10.f);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
          view.move(0.f, 10.f);
        }
      }

      window.clear(sf::Color::Black);

      window.setView(view);

      window.draw(sprite);

      window.display();
    }
  }
}