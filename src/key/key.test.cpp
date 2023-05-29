#include "key.hpp"

#include "../../test/doctest.h"
#include "../entities/character/character.hpp"
#include "../map/map.hpp"

TEST_CASE("Testing the Key class") {
  tmx::Map tiled_map;

  tiled_map.load("assets/map/map0.tmx");

  fnad::Map map{tiled_map};

  fnad::Key key{{0.f, 0.f}, {32.f, 32.f}};
  fnad::Character character{map, {10.f, 10.f}};

  SUBCASE("Key is taken") {
    key.checkTaken(character);

    CHECK(key.getTaken() == true);
  }

  SUBCASE("Key is not taken") {
    character.move({100.f, 100.f});

    key.checkTaken(character);

    CHECK(key.getTaken() == false);
  }
}