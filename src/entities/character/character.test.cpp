#include "character.hpp"

#include "../../../test/doctest.h"
#include "../enemy/enemy.hpp"

TEST_CASE("Testing the Character class") {
  fnad::Character character;

  SUBCASE("Move character") {
    sf::Time time{sf::seconds(1.f)};

    character.move(fnad::Direction::up, time);
    CHECK(character.getPosition() == sf::Vector2f{0.f, -1.f});

    character.move(fnad::Direction::right, time);
    CHECK(character.getPosition() == sf::Vector2f{1.f, -1.f});

    character.move(fnad::Direction::down, time);
    CHECK(character.getPosition() == sf::Vector2f{1.f, 0.f});

    character.move(fnad::Direction::left, time);
    CHECK(character.getPosition() == sf::Vector2f{0.f, 0.f});
  }

  SUBCASE("Check contact with infectious enemy") {
    fnad::Enemy infectious(fnad::Status::infectious);

    CHECK_EQ(character.checkContact(infectious), true);
    CHECK_EQ(character.getLifePoints(), 2);

    character.move(fnad::Direction::down, sf::seconds(100.f));
    CHECK_EQ(character.checkContact(infectious), false);
    CHECK_EQ(character.getLifePoints(), 2);

    fnad::Enemy another_floor(fnad::Status::infectious, fnad::Floor::second,
                              sf::Vector2f{0.f, 0.f});
    CHECK_EQ(character.checkContact(another_floor), false);
    CHECK_EQ(character.getLifePoints(), 2);
  }

  SUBCASE("Check contact with non infectious enemy") {
    fnad::Enemy susceptible(fnad::Status::susceptible);

    CHECK_EQ(character.checkContact(susceptible), false);
  }
}