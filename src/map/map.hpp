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
  const std::vector<Wall> walls_;
  const std::vector<Spawner> spawners_;
  const std::vector<Exit> exits_;
  std::vector<Key> keys_;

  /**
   * Convert a tmx::Object to an entity of the game that accepts
   * a position and a size as its constructor arguments.
   *
   * @param object the object to convert
   * @return an object constructed with the class T
   */
  template <class T>
  static T convertObject(tmx::Object const&);

  /**
   * Parse an entire tmx::ObjectGroup layer into a vector of elements of a
   * certain class T.
   *
   * @param layer the layer to parse
   * @return a vector of T objects
   */
  template <class T>
  static std::vector<T> parseLayer(tmx::ObjectGroup const&);

  void draw(sf::RenderTarget&, sf::RenderStates) const override;

  /**
   * Construct a Map from vectors of walls, spawners, exits and keys.
   *
   * @param walls a vector of walls
   * @param spawners a vector of spawners
   * @param exits a vector of exits
   * @param keys a vector of keys
   */
  Map(std::vector<Wall> const&, std::vector<Spawner> const&,
      std::vector<Exit> const&, std::vector<Key> const&);

 public:
  // Get all walls in the map
  std::vector<Wall> const& getWalls() const;
  // Get all spawners in the map
  std::vector<Spawner> const& getSpawners() const;
  // Get all exits in the map
  std::vector<Exit> const& getExits() const;
  // Get all keys in the map
  std::vector<Key> const& getKeys() const;

  /**
   * Static method to create a map without loading textures for the keys.
   * Should be used for testing purpose only.
   *
   * @param map a parsed tmx map
   */
  static Map create(tmx::Map const&);

  /**
   * Static method to create a map and loading textures for the keys.
   *
   * @param map a parsed tmx map
   * @param textures a vector of textures to be used for the keys
   */
  static Map create(tmx::Map const&, std::vector<sf::Texture> const&);

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

  using WallIterator = std::vector<Wall>::const_iterator;
};
}  // namespace fnad

#endif