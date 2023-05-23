#include "map.hpp"

#include <algorithm>
#include <iterator>
#include <tmxlite/Map.hpp>
#include <tmxlite/ObjectGroup.hpp>
#include <vector>

#include "../entities/character/character.hpp"
#include "../spawner/spawner.hpp"

namespace fnad {
void Map::draw(sf::RenderTarget& target, sf::RenderStates) const {
  for (auto const& key : keys_) {
    if (key.getTaken() == false) {
      target.draw(key);
    }
  }
}

Map::Map(std::vector<Wall> const& walls, std::vector<Spawner> const& spawners,
         std::vector<Exit> const& exits, std::vector<Key> const& keys)
    : walls_{walls}, spawners_{spawners}, exits_{exits}, keys_{keys} {}

std::vector<Wall> const& Map::getWalls() const { return walls_; }

std::vector<Spawner> const& Map::getSpawners() const { return spawners_; }

template <class T>
T Map::convertObject(tmx::Object const& o) {
  auto const& AABB = o.getAABB();

  return T(sf::Vector2f{AABB.left, AABB.top},
           sf::Vector2f{AABB.width, AABB.height});
}

template <class T>
std::vector<T> Map::parseLayer(tmx::ObjectGroup const& layer) {
  auto const& layer_objects = layer.getObjects();
  std::vector<T> layer_vector;

  std::transform(layer_objects.begin(), layer_objects.end(),
                 std::back_inserter(layer_vector), convertObject<T>);

  return layer_vector;
}

void Map::checkKeysTaken(Character const& character) {
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

Map Map::create(tmx::Map const& map) {
  return create(map, std::vector<sf::Texture>{});
}

Map Map::create(tmx::Map const& map,
                std::vector<sf::Texture> const& key_textures) {
  auto const& layers = map.getLayers();

  // Read objects from the first layer and write them to `walls` vector
  auto const& wall_layer = layers[0]->getLayerAs<tmx::ObjectGroup>();
  auto const& walls = parseLayer<Wall>(wall_layer);

  // Read objects from the second layer and write them to `spawners` vector
  auto const& spawner_layer = layers[1]->getLayerAs<tmx::ObjectGroup>();
  auto const& spawners = parseLayer<Spawner>(spawner_layer);

  // Read objects from the third layer and write them to `exits` vector
  auto const& exit_layer = layers[2]->getLayerAs<tmx::ObjectGroup>();
  auto const& exits = parseLayer<Exit>(exit_layer);

  // Read objects from the third layer and write them to `exits` vector
  auto const& key_layer = layers[3]->getLayerAs<tmx::ObjectGroup>();
  auto const& key_layer_objects = key_layer.getObjects();
  std::vector<Key> keys;
  unsigned int key_count{};

  auto const should_load_textures = key_textures.size() > 0;

  std::transform(
      key_layer_objects.begin(), key_layer_objects.end(),
      std::back_inserter(keys),
      [&key_textures, &key_count, &should_load_textures](tmx::Object const& o) {
        auto key = convertObject<Key>(o);

        if (should_load_textures) {
          auto i = key_count % 3;

          key.setTexture(&key_textures[i]);

          key_count++;
        }

        return key;
      });

  return Map(walls, spawners, exits, keys);
}
}  // namespace fnad