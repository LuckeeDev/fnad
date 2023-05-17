#include "map.hpp"

#include <tmxlite/Map.hpp>
#include <tmxlite/ObjectGroup.hpp>
#include <vector>

namespace fnad {
Map::Map(std::vector<Room> rooms) : rooms_{rooms} {}

std::vector<Room> const& Map::getRooms() const { return rooms_; }

Map Map::create(tmx::Map const& map) {
  auto const& layers = map.getLayers();

  auto const& object_layer = layers[0]->getLayerAs<tmx::ObjectGroup>();

  auto const& objects = object_layer.getObjects();

  std::vector<Room> rooms;

  for (auto const& o : objects) {
    auto const& AABB = o.getAABB();

    Room room{sf::Vector2f{AABB.left, AABB.top},
              sf::Vector2f{AABB.width, AABB.height}};

    rooms.push_back(room);
  }

  return Map(rooms);
}
}  // namespace fnad