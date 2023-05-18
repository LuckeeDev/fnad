#include "map.hpp"

#include <tmxlite/Map.hpp>
#include <tmxlite/ObjectGroup.hpp>
#include <vector>

#include "../spawner/spawner.hpp"

namespace fnad {
Map::Map(std::vector<Wall> walls, std::vector<Spawner> spawners)
    : walls_{walls}, spawners_{spawners} {}

std::vector<Wall> const& Map::getWalls() const { return walls_; }

Map Map::create(tmx::Map const& map) {
  auto const& layers = map.getLayers();

  auto const& wall_object_layer = layers[0]->getLayerAs<tmx::ObjectGroup>();
  auto const& spawner_object_layer = layers[1]->getLayerAs<tmx::ObjectGroup>();

  auto const& wall_objects = wall_object_layer.getObjects();
  auto const& spawner_objects = spawner_object_layer.getObjects();

  std::vector<Wall> walls;

  for (auto const& o : wall_objects) {
    auto const& AABB = o.getAABB();

    Wall wall(sf::Vector2f{AABB.left, AABB.top},
              sf::Vector2f{AABB.width, AABB.height});

    walls.push_back(wall);
  }

  std::vector<Spawner> spawners;

  for (auto const& o : spawner_objects) {
    auto const& AABB = o.getAABB();

    Spawner spawner(sf::Vector2f{AABB.left, AABB.top},
                    sf::Vector2f{AABB.width, AABB.height});

    spawners.push_back(spawner);
  }

  return Map(walls, spawners);
}
}  // namespace fnad