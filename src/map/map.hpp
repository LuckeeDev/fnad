#ifndef MAP_HPP
#define MAP_HPP

#include <SFML/Graphics/Rect.hpp>
#include <tmxlite/Map.hpp>
#include <tmxlite/ObjectGroup.hpp>
#include <vector>

namespace fnad {
using Spawner = sf::FloatRect;  // TODO definire la classe Spawner
using Wall = sf::FloatRect;

class Map {
 private:
  const std::vector<Wall> walls_;
  const std::vector<Spawner> spawners_;

  Map(std::vector<Wall>, std::vector<Spawner>);

 public:
  std::vector<Wall> const& getWalls() const;

  static Map create(tmx::Map const&);
};
}  // namespace fnad

#endif