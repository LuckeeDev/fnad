#include "character.hpp"

#include "../../../test/doctest.h"
#include "../../map/map.hpp"
#include "../enemy/enemy.hpp"

TEST_CASE("Testing the Character class") {
  tmx::Map tiled_map;

  tiled_map.load("assets/map/test.tmx");

  fnad::Map map = fnad::Map::create(tiled_map);

  fnad::Character character{map, sf::Vector2f{0.f, 0.f}, 60.f};

  SUBCASE("Move character") {
    sf::Time time{sf::seconds(1.f)};

    character.resetMovement();
    character.addMovement(fnad::Direction::up);
    character.applyMovement(time);
    CHECK(character.getPosition() == sf::Vector2f{0.f, -60.f});

    character.resetMovement();
    character.addMovement(fnad::Direction::right);
    character.applyMovement(time);
    CHECK(character.getPosition() == sf::Vector2f{60.f, -60.f});

    character.resetMovement();
    character.addMovement(fnad::Direction::down);
    character.applyMovement(time);
    CHECK(character.getPosition() == sf::Vector2f{60.f, 0.f});

    character.resetMovement();
    character.addMovement(fnad::Direction::left);
    character.applyMovement(time);
    CHECK(character.getPosition() == sf::Vector2f{0.f, 0.f});
  }

  SUBCASE("Check contact with infectious enemy") {
    fnad::Enemy infectious(map, character.getPosition(),
                           fnad::Status::infectious);

    CHECK(character.checkContact(infectious) == true);
    CHECK(character.getLifePoints() == 2);

    character.resetMovement();
    character.addMovement(fnad::Direction::down);
    character.applyMovement(sf::seconds(100.f));
    CHECK(character.checkContact(infectious) == false);
    CHECK(character.getLifePoints() == 2);
  }

  SUBCASE("Check contact with non infectious enemy") {
    fnad::Enemy susceptible(map, sf::Vector2f{170.f, 100.f},
                            fnad::Status::susceptible);

    CHECK(character.checkContact(susceptible) == false);
  }
}