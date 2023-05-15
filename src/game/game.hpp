#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>

#include "../map/map.hpp"

// Forward declarations of tmxlite's classes
namespace tmx {
class ObjectGroup;
class TileLayer;
}  // namespace tmx

namespace fnad {
class Game final {
 private:
  sf::RenderWindow window_;
  sf::View view_;

  Character character_;
  Epidemic epidemic_;
  Map map_;

  void gameLoop();

 public:
  void run() const;
};
}  // namespace fnad

#endif