#include "map.hpp"

#include "../../test/doctest.h"
#include "../entities/character/character.hpp"

TEST_CASE("Testing the map class") {
  tmx::Map tiled_map;

  tiled_map.load("assets/map/map0.tmx");

  fnad::Map map = fnad::Map::create(tiled_map);

  fnad::Character character(map, {0.f, 0.f});

  CHECK(map.getWalls().size() == 6);
  CHECK(map.getSpawners().size() == 3);
  CHECK(map.getExits().size() == 1);
  CHECK(map.getKeys().size() == 3);

  character.setPosition({724.f, 68.f});
  map.collectKeys(character);
  CHECK(map.countTakenKeys() == 1);

  character.setPosition({100.f, 100.f});
  map.collectKeys(character);
  CHECK(map.countTakenKeys() == 1);

  character.setPosition({514.f, 35.f});
  map.collectKeys(character);
  CHECK(map.countTakenKeys() == 2);

  character.setPosition({750.f, 140.f});
  map.collectKeys(character);
  CHECK(map.hasWon(character) == false);

  character.setPosition({587.f, 97.f});
  map.collectKeys(character);
  CHECK(map.countTakenKeys() == 3);

  character.setPosition({750.f, 140.f});
  CHECK(map.hasWon(character) == true);
}