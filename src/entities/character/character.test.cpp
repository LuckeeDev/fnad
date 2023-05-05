#include "character.hpp"

#include "../enemy/enemy.hpp"
#include "../test/doctest.h"

TEST_CASE("Testing the Character class") {
  fnad::Character character;

  SUBCASE("Detect contact with infectious enemy") {
    fnad::Enemy infectious(fnad::Status::infectious);
    CHECK_EQ(character.checkContact(infectious), true);
  }

  SUBCASE("Detect contact with non infectious enemy") {
    fnad::Enemy susceptible(fnad::Status::susceptible);
    CHECK_EQ(character.checkContact(susceptible), false);
  }
}