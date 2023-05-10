#include "epidemic.hpp"

#include <iostream>

#include "../../test/doctest.h"

TEST_CASE("Testing Epidemic") {
  SUBCASE("Testing evolve") {
    fnad::Epidemic epidemic(100, sf::Vector2f{960.f, 540.f});

    sf::Time time{sf::seconds(1.f)};

    int s_0{epidemic.count(fnad::Status::susceptible)},
        i_0{epidemic.count(fnad::Status::infectious)},
        r_0{epidemic.count(fnad::Status::removed)};

    for (int i{}; i < 1000; i++) {
      epidemic.evolve(time);
    }

    int s_1{epidemic.count(fnad::Status::susceptible)},
        i_1{epidemic.count(fnad::Status::infectious)},
        r_1{epidemic.count(fnad::Status::removed)};

    CHECK(s_0 == 99);
    CHECK(i_0 == 1);
    CHECK(r_0 == 0);
    CHECK(s_0 + i_0 + r_0 == s_1 + i_1 + r_1);
    CHECK(s_0 != s_1);
    CHECK(i_0 != i_1);
    CHECK(r_0 != r_1);
  }
}