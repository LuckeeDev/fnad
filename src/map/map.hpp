#ifndef MAP_HPP
#define MAP_HPP

#include <tmxlite/Map.hpp>
#include <tmxlite/ObjectGroup.hpp>
#include <vector>

#include "../room/room.hpp"

namespace fnad {
class Map {
 private:
  const std::vector<Room> rooms_;

 public:
  Map(std::vector<Room>);

  std::vector<Room> const &getRooms() const;

  static Map create(tmx::Map const &);
};
}  // namespace fnad

#endif