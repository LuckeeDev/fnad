#include "character.hpp"

#include "../../../test/doctest.h"
#include "../enemy/enemy.hpp"
#include "../../map/map.hpp"

TEST_CASE("Testing the Character class") {
  fnad::Map map{"../../../assets/map/test.tmx"};
  fnad::Character character{map, sf::Vector2f{170.f, 100.f}};

  SUBCASE("Move character") {
    sf::Time time{sf::seconds(1.f)};

    character.move(fnad::Direction::up, time);
    CHECK(character.getPosition() == sf::Vector2f{170.f, 99.f});

    character.move(fnad::Direction::right, time);
    CHECK(character.getPosition() == sf::Vector2f{171.f, 99.f});

    character.move(fnad::Direction::down, time);
    CHECK(character.getPosition() == sf::Vector2f{171.f, 100.f});

    character.move(fnad::Direction::left, time);
    CHECK(character.getPosition() == sf::Vector2f{170.f, 100.f});
  }

  SUBCASE("Check contact with infectious enemy") {
    fnad::Enemy infectious(map, sf::Vector2f{170.f, 100.f}, fnad::Status::infectious);

    CHECK_EQ(character.checkContact(infectious), true);
    CHECK_EQ(character.getLifePoints(), 2);

    character.move(fnad::Direction::down, sf::seconds(100.f));
    CHECK_EQ(character.checkContact(infectious), false);
    CHECK_EQ(character.getLifePoints(), 2);

    // fnad::Enemy another_floor(fnad::Status::infectious, fnad::Floor::second,
    //                           sf::Vector2f{0.f, 0.f});
    // CHECK_EQ(character.checkContact(another_floor), false);
    // CHECK_EQ(character.getLifePoints(), 2);
  }

  SUBCASE("Check contact with non infectious enemy") {
    fnad::Enemy susceptible(map, sf::Vector2f{170.f, 100.f}, fnad::Status::susceptible);

    CHECK_EQ(character.checkContact(susceptible), false);
  }
}