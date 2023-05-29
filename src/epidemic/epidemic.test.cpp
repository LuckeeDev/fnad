#include "epidemic.hpp"

#include <cmath>

#include "../../test/doctest.h"
#include "../entities/character/character.hpp"
#include "../map/map.hpp"

TEST_CASE("Testing Epidemic") {
  tmx::Map tiled_map;

  tiled_map.load("assets/map/map0.tmx");

  fnad::Map map{tiled_map};

  SUBCASE("Testing evolve") {
    sf::View test_view;
    fnad::Epidemic epidemic(99, 1, map, test_view);
    fnad::Character character(map, {0.f, 0.f});

    sf::Time time{sf::seconds(1.f)};

    int s_0{epidemic.count(fnad::Status::susceptible)},
        i_0{epidemic.count(fnad::Status::infectious)},
        r_0{epidemic.count(fnad::Status::removed)};

    for (int i{}; i < 1000; i++) {
      epidemic.evolve(time, character);
    }

    int s_1{epidemic.count(fnad::Status::susceptible)},
        i_1{epidemic.count(fnad::Status::infectious)},
        r_1{epidemic.count(fnad::Status::removed)};

    fnad::SIR sir{epidemic.getSIRState()};

    CHECK(s_0 == 99);
    CHECK(i_0 == 1);
    CHECK(r_0 == 0);

    CHECK(s_0 + i_0 + r_0 == s_1 + i_1 + r_1);

    CHECK(s_0 != s_1);
    CHECK(i_0 != i_1);
    CHECK(r_0 != r_1);

    CHECK(std::round(sir.s_) == std::round(s_1));
    CHECK(std::round(sir.i_) == std::round(i_1));
    CHECK(std::round(sir.r_) == std::round(r_1));
  }
}