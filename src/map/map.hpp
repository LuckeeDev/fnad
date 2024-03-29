#ifndef MAP_HPP
#define MAP_HPP

#include <SFML/Graphics.hpp>
#include <tmxlite/Map.hpp>
#include <tmxlite/Object.hpp>
#include <vector>

#include "../key/key.hpp"
#include "../spawner/spawner.hpp"

namespace fnad {
using Wall = sf::FloatRect;
using Exit = sf::FloatRect;

class Map final : public sf::Drawable {
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
   * Create a map with keys.
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
   * @return how many keys are in the game
   */
  int countKeys() const;

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