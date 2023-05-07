#include "enemy.hpp"

#include <cmath>

#include "../../../test/doctest.h"
#include "../character/character.hpp"

TEST_CASE("Testing the Enemy class") {
  fnad::Enemy enemy;

  SUBCASE("Calling evolve moves the enemy") {
    enemy.setStatus(fnad::Status::infectious);
    auto position_before = enemy.getPosition();
    auto floor_before = enemy.getFloor();

    sf::Time time{sf::seconds(1.f)};

    fnad::Character character;
    character.setPosition(15.79865f, 20.153f);

    enemy.evolve(time, character);

    auto position_after = enemy.getPosition();
    auto floor_after = enemy.getFloor();

    CHECK_EQ(floor_before, floor_after);  // checking that Enemy::evolve does
                                          // not change enemy's floor

    float distance = static_cast<float>(
        std::sqrt(std::pow((position_after.x - position_before.x), 2) +
                  std::pow((position_after.y - position_before.y), 2)));

    CHECK_EQ(distance, 1.f);  // checking distance after calling Enemy::evolve

    character.setPosition(23.156f, 48.2674f);

    position_before = enemy.getPosition();
    enemy.evolve(time, character);
    position_after = enemy.getPosition();

    distance = static_cast<float>(
        std::sqrt(std::pow((position_after.x - position_before.x), 2) +
                  std::pow((position_after.y - position_before.y), 2)));

    CHECK_EQ(distance, 1.f);  // checking distance after calling Enemy::evolve
                              // whith character in a different position

    enemy.setSpeed(2.f);
    enemy.setPosition(0.f, 0.f);

    position_before = enemy.getPosition();
    enemy.evolve(time, character);
    position_after = enemy.getPosition();

    distance = static_cast<float>(
        std::sqrt(std::pow((position_after.x - position_before.x), 2) +
                  std::pow((position_after.y - position_before.y), 2)));

    CHECK_EQ(distance, 2.f);  // checking the dependence of distance on speed

    time = sf::seconds(5.f);
    enemy.setPosition(0.f, 0.f);

    position_before = enemy.getPosition();
    enemy.evolve(time, character);
    position_after = enemy.getPosition();

    distance = static_cast<float>(
        std::sqrt(std::pow((position_after.x - position_before.x), 2) +
                  std::pow((position_after.y - position_before.y), 2)));

    CHECK_EQ(distance, 10.f);  // checking the dependence of distance on time

    enemy.setSpeed(1.f);
    enemy.setPosition(0.f, 0.f);
    character.setPosition(4.f, 3.f);

    enemy.evolve(time, character);

    CHECK_EQ(enemy.getPosition(),
             character.getPosition());  // checking the direction of enemy's
                                        // motion after calling Enemy::evolve

    character.setFloor(fnad::Floor::roof);

    position_before = enemy.getPosition();
    enemy.evolve(time, character);
    position_after = enemy.getPosition();

    CHECK_EQ(position_before,
             position_after);  // checking Enemy::evolve when character and
                               // enemy are on different floors

    character.setFloor(enemy.getFloor());
    character.setPosition(enemy.getPosition());

    position_before = enemy.getPosition();
    enemy.evolve(time, character);
    position_after = enemy.getPosition();

    CHECK_EQ(position_before,
             position_after);  // checking Enemy::evolve when character and
                               // enemy share the same position and floor

    character.setPosition(1561.f, 2478.f);
    enemy.setStatus(fnad::Status::susceptible);

    position_before = enemy.getPosition();
    enemy.evolve(time, character);
    position_after = enemy.getPosition();

    CHECK_EQ(
        position_before,
        position_after);  // checking Enemy::evolve when enemy is subsceptible

    enemy.setStatus(fnad::Status::removed);

    position_before = enemy.getPosition();
    enemy.evolve(time, character);
    position_after = enemy.getPosition();

    CHECK_EQ(position_before,
             position_after);  // checking Enemy::evolve when enemy is removed
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