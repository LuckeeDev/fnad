#include "background.hpp"

#include "../../test/doctest.h"

TEST_CASE("Testing the Background class") {
  tmx::Map tiled_map;

  SUBCASE("Test size of the test map") {
    tiled_map.load("assets/map/map0.tmx");
    fnad::Background background{tiled_map};

    CHECK(background.getSize() == sf::Vector2u{960, 640});
  }

  SUBCASE("Test size of the game map") {
    tiled_map.load("assets/map/difa_map.tmx");
    fnad::Background background{tiled_map};

    CHECK(background.getSize() == sf::Vector2u{5120, 3840});
  }
}