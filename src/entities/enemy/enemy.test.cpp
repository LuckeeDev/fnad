#include "enemy.hpp"

#include <cmath>

#include "../../../test/doctest.h"
#include "../character/character.hpp"

TEST_CASE("Testing the Enemy class") {
  fnad::Enemy enemy;

  SUBCASE("Calling evolve moves the enemy") {
    auto position_before = enemy.getPosition();
    auto floor_before = enemy.getFloor();

    sf::Time time{sf::seconds(1.f)};
    fnad::Character character;

    enemy.evolve(time, character);

    auto position_after = enemy.getPosition();
    auto floor_after = enemy.getFloor();

    CHECK_EQ(floor_before, floor_after);

    auto distance =
        std::sqrt(std::pow((position_after.x - position_before.x), 2) +
                  std::pow((position_after.y - position_before.y), 2));

    CHECK_EQ(distance, 1.f);
  }

  SUBCASE("Calling infect changes the status") {
    enemy.infect();

    auto status_after = enemy.getStatus();

    CHECK_EQ(status_after, fnad::Status::infectious);
  }

  SUBCASE("Calling infect on an infected enemy throws") {
    enemy.infect();

    CHECK_THROWS(enemy.infect());
  }
}