#include "entity.hpp"

#include "../../../test/doctest.h"
#include "../../map/map.hpp"

TEST_CASE("Testing the Entity class") {
  tmx::Map tiled_map;

  tiled_map.load("assets/map/map0.tmx");

  fnad::Map map{tiled_map};
  fnad::Entity entity{map, {171.f, 200.f}, 100.f};

  SUBCASE("Testing speed methods") {
    CHECK(entity.getSpeed() == 100.f);

    entity.setSpeed(150.f);

    CHECK(entity.getSpeed() == 150.f);
  }

  SUBCASE("Testing the safeMove method") {
    fnad::Collision collision;

    // Check collision moving right
    collision = entity.safeMove({15.f, 5.f});
    CHECK(entity.getPosition() == sf::Vector2f{176.f, 205.f});
    CHECK(collision == fnad::Collision{true, false});

    // Check collision moving down
    entity.setPosition({246.f, 64.f});
    collision = entity.safeMove({3.f, 12.f});
    CHECK(entity.getPosition() == sf::Vector2f{249.f, 72.f});

    CHECK(collision == fnad::Collision{false, true});

    // Check collision moving left
    entity.setPosition({246.f, 167.f});
    collision = entity.safeMove({-10.f, 5.3f});

    CHECK(entity.getPosition() == sf::Vector2f{240.f, 172.3f});
    CHECK(collision == fnad::Collision{true, false});

    // Check collision moving up
    entity.setPosition({250.f, 160.f});
    collision = entity.safeMove({2.f, -13.2f});

    CHECK(entity.getPosition() == sf::Vector2f{252.f, 152.f});
    CHECK(collision == fnad::Collision{false, true});
  }
}