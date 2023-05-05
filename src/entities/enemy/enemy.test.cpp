#include "enemy.hpp"

#include <cmath>

#include "../test/doctest.h"

TEST_CASE("Testing the Enemy class") {
  fnad::Enemy enemy;

  SUBCASE("Calling evolve moves the enemy") {
    auto position_before = enemy.position();

    sf::Time time{sf::seconds(1.f)};
    fnad::Character character;

    enemy.evolve(time, character);

    auto position_after = enemy.position();

    CHECK_EQ(position_before.floor, position_after.floor);

    auto distance = std::sqrt(
        std::pow((position_after.coordinates.x - position_before.coordinates.x),
                 2) +
        std::pow((position_after.coordinates.y - position_before.coordinates.y),
                 2));

    CHECK_EQ(distance, doctest::Approx(time.asSeconds() * enemy.speed()));
  }

  SUBCASE("Calling infect changes the status") {
    enemy.infect();

    auto status_after = enemy.status();

    CHECK_EQ(status_after, fnad::Status::infectious);
  }

  SUBCASE("Calling infect on an infected enemy throws") {
    enemy.infect();

    CHECK_THROWS(enemy.infect());
  }
}