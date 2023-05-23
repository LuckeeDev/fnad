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
std::vector<T> Map::parseLayer(tmx::ObjectGroup const& layer) {
  auto const& layer_objects = layer.getObjects();
  std::vector<T> layer_vector;

  std::transform(layer_objects.begin(), layer_objects.end(),
                 std::back_inserter(layer_vector), [](tmx::Object const& o) {
                   auto const& AABB = o.getAABB();

                   return T(sf::Vector2f{AABB.left, AABB.top},
                            sf::Vector2f{AABB.width, AABB.height});
                 });

  return layer_vector;
}

Map Map::create(tmx::Map const& map) {
  auto const& layers = map.getLayers();

  // Read objects from the first layer and write them to `walls` vector
  auto const& wall_layer = layers[0]->getLayerAs<tmx::ObjectGroup>();
  auto const& walls = parseLayer<Wall>(wall_layer);

  // Read objects from the second layer and write them to `spawners` vector
  auto const& spawner_layer = layers[1]->getLayerAs<tmx::ObjectGroup>();
  auto const& spawners = parseLayer<Spawner>(spawner_layer);

  return Map(walls, spawners);
}
}  // namespace fnad