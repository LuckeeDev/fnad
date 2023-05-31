#include "map.hpp"

#include <algorithm>
#include <iterator>
#include <tmxlite/Map.hpp>
#include <tmxlite/ObjectGroup.hpp>
#include <vector>

#include "../entities/character/character.hpp"
#include "../spawner/spawner.hpp"

namespace fnad {
// Constructors

Map::Map(tmx::Map const& map) {
  auto const& layers = map.getLayers();

  // Read objects from the first layer and write them to `walls` vector
  auto const& wall_layer = layers[0]->getLayerAs<tmx::ObjectGroup>();
  parseLayerInto<Wall>(wall_layer, walls_);

  // Read objects from the second layer and write them to `spawners` vector
  auto const& spawner_layer = layers[1]->getLayerAs<tmx::ObjectGroup>();
  parseLayerInto<Spawner>(spawner_layer, spawners_);

  // Read objects from the third layer and write them to `exits` vector
  auto const& exit_layer = layers[2]->getLayerAs<tmx::ObjectGroup>();
  parseLayerInto<Exit>(exit_layer, exits_);

  // Read objects from the fourth layer and write them to `keys` vector
  auto const& key_layer = layers[3]->getLayerAs<tmx::ObjectGroup>();
  auto const& key_layer_objects = key_layer.getObjects();

  int key_index{};

  std::transform(
      key_layer_objects.begin(), key_layer_objects.end(),
      std::back_inserter(keys_), [&key_index, this](tmx::Object const& o) {
        auto const& AABB = o.getAABB();
        Key key{
            {AABB.left, AABB.top}, {AABB.width, AABB.height}, key_index % 3};

        key_index++;

        return key;
      });
}

// Private functions

void Map::draw(sf::RenderTarget& target, sf::RenderStates) const {
  for (auto const& key : keys_) {
    auto const& key_rect = key.getGlobalBounds();
    auto const& view = target.getView();

    sf::FloatRect const view_rect{view.getCenter() - view.getSize() / 2.f,
                                  view.getSize()};

    if (key.getTaken() == false && key_rect.intersects(view_rect)) {
      target.draw(key);
    }
  }
}

template <class T>
void Map::parseLayerInto(tmx::ObjectGroup const& layer,
                         std::vector<T>& layer_vector) {
  auto const& layer_objects = layer.getObjects();

  std::transform(layer_objects.begin(), layer_objects.end(),
                 std::back_inserter(layer_vector), [](tmx::Object const& o) {
                   auto const& AABB = o.getAABB();

                   return T({AABB.left, AABB.top}, {AABB.width, AABB.height});
                 });
};

// Public functions

std::vector<Wall> const& Map::getWalls() const { return walls_; }
std::vector<Spawner>& Map::getSpawners() { return spawners_; }
std::vector<Exit> const& Map::getExits() const { return exits_; }
std::vector<Key> const& Map::getKeys() const { return keys_; }

void Map::collectKeys(Character const& character) {
  for (auto& key : keys_) {
    key.checkTaken(character);
  }
}

bool Map::hasWon(Character const& character) const {
  auto const is_on_exit =
      std::any_of(exits_.begin(), exits_.end(), [&character](Exit const& exit) {
        auto const& character_rect = character.getGlobalBounds();

        return exit.intersects(character_rect);
      });

  return is_on_exit &&
         std::all_of(keys_.begin(), keys_.end(),
                     [](Key const& key) { return key.getTaken(); });
};

int Map::countTakenKeys() const {
  return static_cast<int>(
      std::count_if(keys_.begin(), keys_.end(),
                    [](Key const& key) { return key.getTaken(); }));
}
}  // namespace fnad