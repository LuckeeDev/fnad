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

  template <class T>
  static T convertObject(tmx::Object const&);

  template <class T>
  static std::vector<T> parseLayer(tmx::ObjectGroup const& layer);

  Map(std::vector<Wall> const&, std::vector<Spawner> const&,
      std::vector<Exit> const&, std::vector<Key> const&);

  void draw(sf::RenderTarget&, sf::RenderStates) const override;

 public:
  std::vector<Wall> const& getWalls() const;
  std::vector<Spawner> const& getSpawners() const;

  static Map create(tmx::Map const&);
  static Map create(tmx::Map const&, std::vector<sf::Texture> const&);

  void checkKeysTaken(Character const&);
  bool hasWon(Character const&) const;

  using WallIterator = std::vector<Wall>::const_iterator;
};
}  // namespace fnad

#endif