#ifndef MAP_HPP
#define MAP_HPP

#include <SFML/Graphics/Rect.hpp>
#include <tmxlite/Map.hpp>
#include <tmxlite/Object.hpp>
#include <vector>

#include "../key/key.hpp"
#include "../spawner/spawner.hpp"

namespace fnad {
using Wall = sf::FloatRect;
using Exit = sf::FloatRect;

class Map : public sf::Drawable {
 private:
  std::vector<Wall> walls_;
  std::vector<Spawner> spawners_;
  std::vector<Exit> exits_;
  std::vector<Key> keys_;

  /**
   * Parse an entire tmx::ObjectGroup layer into a vector of elements of a
   * certain class T.
   *
   * @param layer the layer to parse
   * @param layer_vector a vector of T objects to push back the newly created
   * objects
   */
  template <class T>
  void parseLayerInto(tmx::ObjectGroup const&, std::vector<T>&);

  void draw(sf::RenderTarget&, sf::RenderStates) const override;

 public:
  /**
   * Create a map with textured keys.
   *
   * @param map a parsed Tiled map
   * @param key_textures a vector of `sf::Texture` to be used for the keys
   */
  Map(tmx::Map const& map, std::vector<sf::Texture> const& key_textures);

  /**
   * Create a map without textured keys. This should be used for testing purpose
   * only.
   *
   * @param map a parsed Tiled map
   */
  Map(tmx::Map const& map);

  // Get all walls in the map
  std::vector<Wall> const& getWalls() const;
  // Get all spawners in the map
  std::vector<Spawner>& getSpawners();
  // Get all exits in the map
  std::vector<Exit> const& getExits() const;
  // Get all keys in the map
  std::vector<Key> const& getKeys() const;

  /**
   * Allow the player to collect keys. It checks for intersections
   * between the Character and all keys.
   *
   * @param character the character used to check for intersections
   */
  void collectKeys(Character const&);

  /**
   * Count how many keys have been collected.
   *
   * @return the number of keys marked as "taken"
   */
  int countTakenKeys() const;

  /**
   * Check if the player has won. That means that the player
   * is currently on an Exit and all keys in the Map are marked as "taken".
   *
   * @return true if the player has won, false otherwise
   */
  bool hasWon(Character const&) const;
};
}  // namespace fnad

#endif