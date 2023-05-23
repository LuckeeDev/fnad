#include "map.hpp"

#include <iterator>
#include <tmxlite/Map.hpp>
#include <tmxlite/ObjectGroup.hpp>
#include <vector>

#include "../spawner/spawner.hpp"

namespace fnad {
Map::Map(std::vector<Wall> const& walls, std::vector<Spawner> const& spawners)
    : walls_{walls}, spawners_{spawners} {}

std::vector<Wall> const& Map::getWalls() const { return walls_; }

std::vector<Spawner> const& Map::getSpawners() const { return spawners_; }

template <class T>
T Map::convertObject(tmx::Object const& o) {
  auto const& AABB = o.getAABB();

  return T(sf::Vector2f{AABB.left, AABB.top},
           sf::Vector2f{AABB.width, AABB.height});
}

Map Map::create(tmx::Map const& map) {
  auto const& layers = map.getLayers();

  // Read objects from the first layer and write them to `walls` vector
  auto const& wall_object_layer = layers[0]->getLayerAs<tmx::ObjectGroup>();
  auto const& wall_objects = wall_object_layer.getObjects();
  std::vector<Wall> walls;

  std::transform(wall_objects.begin(), wall_objects.end(),
                 std::back_inserter(walls), convertObject<Wall>);

  // Read objects from the second layer and write them to `spawners` vector
  auto const& spawner_object_layer = layers[1]->getLayerAs<tmx::ObjectGroup>();
  auto const& spawner_objects = spawner_object_layer.getObjects();
  std::vector<Spawner> spawners;

  std::transform(spawner_objects.begin(), spawner_objects.end(),
                 std::back_inserter(spawners), convertObject<Spawner>);

  return Map(walls, spawners);
}
}  // namespace fnad