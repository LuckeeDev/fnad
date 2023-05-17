#ifndef MAP_HPP
#define MAP_HPP

#include <SFML/Graphics/Rect.hpp>
#include <tmxlite/Map.hpp>
#include <tmxlite/ObjectGroup.hpp>
#include <vector>

namespace fnad {
using Room = sf::FloatRect;
using Wall = sf::FloatRect;

class Map {
 private:
  const std::vector<Room> rooms_;

  Map(std::vector<Room>);

 public:
  std::vector<Room> const &getRooms() const;

  static Map create(tmx::Map const &);
};
}  // namespace fnad

#endif