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
  static T convertObject(tmx::Object const&);

  Map(std::vector<Wall>, std::vector<Spawner>);

 public:
  std::vector<Wall> const& getWalls() const;

  static Map create(tmx::Map const&);
};
}  // namespace fnad

#endif