#include "src/game/game.hpp"
#include "src/map/map.hpp"

int main() {
  sf::RenderWindow window(sf::VideoMode(960, 640), "Map test");
  window.setFramerateLimit(60);

  sf::View view(sf::Vector2f(100.f, 100.f), sf::Vector2f(300.f, 200.f));

  tmx::Map tiled_map;

  if (tiled_map.load("assets/map/test.tmx")) {
    const fnad::Map map = fnad::Map::create(tiled_map);

    const fnad::Background background(tiled_map);

    fnad::Epidemic epidemic(99, 1, map, view);

    fnad::Character character(map, sf::Vector2f{0.f, 0.f});

    fnad::Game game(window, view, character, epidemic, map, background);

    game.run();
  }
}