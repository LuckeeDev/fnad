#include "character.hpp"

#include "../enemy/enemy.hpp"
#include "../test/doctest.h"

TEST_CASE("Testing the Character class") {
  Character character;

  SUBCASE("Detect contact with infectious enemy") {
    Enemy infectious(Status::infectious);
    CHECK_EQ(character.checkContact(infectious&), true);
  }

  SUBCASE("Detect contact with non infectious enemy") {
    Enemy susceptible(Status::susceptible);
    CHECK_EQ(character.checkContact(susceptible&), false);
  }
}