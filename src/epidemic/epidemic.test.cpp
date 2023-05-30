#include "epidemic.hpp"

#include <cmath>

#include "../../test/doctest.h"
#include "../entities/character/character.hpp"
#include "../map/map.hpp"

TEST_CASE("Testing Epidemic") {
  tmx::Map tiled_map;

  tiled_map.load("assets/map/map0.tmx");

  fnad::Map map{tiled_map};

  fnad::Epidemic epidemic;

  SUBCASE("Testing SIR state handling") {
    epidemic.resetSIRState({34, 653, 10}, map);

    // It should only create susceptible and infectious enemies
    CHECK(epidemic.getEnemies().size() == 687);
    CHECK(epidemic.getSIRState().s == 34.);
    CHECK(epidemic.getSIRState().i == 653.);
    CHECK(epidemic.getSIRState().r == 10.);

    epidemic.resetSIRState({2, 55, 0}, map);

    CHECK(epidemic.getEnemies().size() == 57);
    CHECK(epidemic.getSIRState().s == 2.);
    CHECK(epidemic.getSIRState().i == 55.);
    CHECK(epidemic.getSIRState().r == 0.);
  }

  SUBCASE("Testing the evolve method") {
    epidemic.resetSIRState({99, 1, 0}, map);

    const fnad::Character character(map, {0.f, 0.f});

    // Test count method
    const int s_0{epidemic.count(fnad::Status::susceptible)},
        i_0{epidemic.count(fnad::Status::infectious)},
        r_0{epidemic.count(fnad::Status::removed)};

    CHECK(s_0 == 99);
    CHECK(i_0 == 1);
    CHECK(r_0 == 0);

    // Check what happens after evolving for half a day
    sf::Time time{sf::seconds(1.f)};

    epidemic.evolve(time, character);

    auto sir = epidemic.getSIRState();

    CHECK(sir.s == doctest::Approx(98.6535));
    CHECK(sir.i == doctest::Approx(1.3215));
    CHECK(sir.r == doctest::Approx(0.025));

    CHECK(sir.s + sir.i + sir.r == doctest::Approx(100));

    // Check what happens after evolving for a full day
    time = sf::seconds(2.f);

    epidemic.evolve(time, character);

    sir = epidemic.getSIRState();

    CHECK(sir.s == doctest::Approx(97.7409));
    CHECK(sir.i == doctest::Approx(2.168));
    CHECK(sir.r == doctest::Approx(0.091075));

    CHECK(sir.s + sir.i + sir.r == doctest::Approx(100));

    // Evolve for 500 days and check what happens
    for (int i{}; i < 1000; i++) {
      epidemic.evolve(time, character);
    }

    const int s_1{epidemic.count(fnad::Status::susceptible)},
        i_1{epidemic.count(fnad::Status::infectious)},
        r_1{epidemic.count(fnad::Status::removed)};

    sir = epidemic.getSIRState();

    CHECK(s_0 + i_0 + r_0 == s_1 + i_1 + r_1);

    CHECK(s_0 != s_1);
    CHECK(i_0 != i_1);
    CHECK(r_0 != r_1);

    CHECK(std::round(sir.s) == std::round(s_1));
    CHECK(std::round(sir.i) == std::round(i_1));
    CHECK(std::round(sir.r) == std::round(r_1));
  }
}