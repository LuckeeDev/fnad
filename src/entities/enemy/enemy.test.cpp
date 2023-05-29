#include "enemy.hpp"

#include <cmath>

#include "../../../test/doctest.h"
#include "../../map/map.hpp"
#include "../character/character.hpp"

TEST_CASE("Testing the Enemy class") {
  tmx::Map tiled_map;

  tiled_map.load("assets/map/map0.tmx");

  fnad::Map map{tiled_map};

  SUBCASE("Calling evolve moves the enemy") {
    fnad::Enemy enemy(map, sf::Vector2f{0.f, 0.f}, fnad::Status::infectious,
                      30.f);
    sf::Time time{sf::seconds(1.f)};
    fnad::Character character{map, sf::Vector2f{15.79865f, 20.153f}};

    SUBCASE("With infected enemy") {
      auto position_before = enemy.getPosition();

      enemy.evolve(time, character);

      auto position_after = enemy.getPosition();

      float distance = static_cast<float>(
          std::sqrt(std::pow((position_after.x - position_before.x), 2) +
                    std::pow((position_after.y - position_before.y), 2)));

      // Test distance traveled after calling evolve
      CHECK(distance == 45.f);

      // Test distance traveled after calling evolve with character in a
      // different position
      character.setPosition(23.156f, 48.2674f);

      position_before = enemy.getPosition();
      enemy.evolve(time, character);
      position_after = enemy.getPosition();

      distance = static_cast<float>(
          std::sqrt(std::pow((position_after.x - position_before.x), 2) +
                    std::pow((position_after.y - position_before.y), 2)));

      CHECK(distance == doctest::Approx(45.f));

      // Test the dependence of distance on speed
      enemy.setSpeed(2.f);
      enemy.setPosition(0.f, 0.f);

      position_before = enemy.getPosition();
      enemy.evolve(time, character);
      position_after = enemy.getPosition();

      distance = static_cast<float>(
          std::sqrt(std::pow((position_after.x - position_before.x), 2) +
                    std::pow((position_after.y - position_before.y), 2)));

      CHECK(distance == doctest::Approx(3.f));

      // Test the dependence of distance on time
      time = sf::seconds(5.f);
      enemy.setPosition(0.f, 0.f);

      position_before = enemy.getPosition();
      enemy.evolve(time, character);
      position_after = enemy.getPosition();

      distance = static_cast<float>(
          std::sqrt(std::pow((position_after.x - position_before.x), 2) +
                    std::pow((position_after.y - position_before.y), 2)));

      CHECK(distance == doctest::Approx(15.f));

      // Check the direction of enemy's motion after calling evolve
      enemy.setSpeed(2.f);
      enemy.setPosition(0.f, 0.f);
      character.setPosition(12.f, 9.f);

      enemy.evolve(time, character);

      CHECK(enemy.getPosition() == character.getPosition());

      character.setPosition(enemy.getPosition());

      position_before = enemy.getPosition();
      enemy.evolve(time, character);
      position_after = enemy.getPosition();

      CHECK(position_before == position_after);
    }

    SUBCASE("With susceptible enemy") {
      // Test that evolve does not move the enemy when it is subsceptible
      fnad::Enemy susceptible(map, sf::Vector2f{0.f, 0.f},
                              fnad::Status::susceptible, 30.f);

      auto position_before = susceptible.getPosition();
      susceptible.evolve(time, character);
      auto position_after = susceptible.getPosition();

      CHECK(position_before != position_after);

      auto displacement =
          std::sqrt(std::pow(position_after.x - position_before.x, 2.f) +
                    std::pow(position_after.y - position_before.y, 2.f));

      CHECK(displacement == doctest::Approx(30.f));
    }

    SUBCASE("With removed enemy") {
      // Test that evolve does not move the enemy when it is subsceptible
      fnad::Enemy removed(map, sf::Vector2f{0.f, 0.f}, fnad::Status::removed,
                          30.f);

      auto position_before = removed.getPosition();
      removed.evolve(time, character);
      auto position_after = removed.getPosition();

      CHECK(position_before == position_after);
    }
  }

  SUBCASE("Testing infect and remove method") {
    fnad::Enemy enemy(map, sf::Vector2f{0.f, 0.f}, fnad::Status::susceptible);

    enemy.infect();

    CHECK(enemy.getStatus() == fnad::Status::infectious);

    CHECK_THROWS(enemy.infect());

    enemy.remove();

    CHECK(enemy.getStatus() == fnad::Status::removed);

    CHECK_THROWS(enemy.remove());
  }

  SUBCASE("Testing the sees method") {
    fnad::Enemy hidden_enemy(map, {154.f, 223.f}, fnad::Status::infectious,
                             30.f);
    fnad::Enemy visible_enemy(map, {239.f, 141.f}, fnad::Status::infectious,
                              30.f);
    fnad::Character character(map, {314.f, 219.f});

    CHECK(hidden_enemy.sees(character) == false);
    CHECK(visible_enemy.sees(character) == true);
  }
}