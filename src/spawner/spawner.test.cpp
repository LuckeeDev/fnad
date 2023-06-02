#include "spawner.hpp"

#include <SFML/Graphics.hpp>

#include "../../test/doctest.h"

TEST_CASE("Testing the Spawner class") {
  sf::Vector2f position{200.f, 150.f};
  sf::Vector2f size{100.f, 50.f};
  fnad::Spawner spawner{position, size};

  CHECK(spawner.getArea() == 5000.);

  auto coordinates = spawner.getSpawnPoint();

  CHECK(coordinates.x >= 200.f);
  CHECK(coordinates.x <= 300.f);
  CHECK(coordinates.y >= 150.f);
  CHECK(coordinates.y <= 200.f);
}