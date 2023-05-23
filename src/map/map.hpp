#ifndef MAP_HPP
#define MAP_HPP

#include <SFML/Graphics/Rect.hpp>
#include <tmxlite/Map.hpp>
#include <tmxlite/Object.hpp>
#include <vector>

#include "../spawner/spawner.hpp"

namespace fnad {
using Wall = sf::FloatRect;

class Map {
 private:
  const std::vector<Wall> walls_;
  const std::vector<Spawner> spawners_;

  template <class T>
  static std::vector<T> parseLayer(tmx::ObjectGroup const& layer);

  Map(std::vector<Wall> const&, std::vector<Spawner> const&);

 public:
  std::vector<Wall> const& getWalls() const;
  std::vector<Spawner> const& getSpawners() const;

  static Map create(tmx::Map const&);

  using WallIterator = std::vector<Wall>::const_iterator;
};
}  // namespace fnad

#endif