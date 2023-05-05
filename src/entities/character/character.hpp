#ifndef CHARACTER_HPP
#define CHARACTER_HPP

#include <SFML/Graphics.hpp>

#include "../../common/position.hpp"
#include "../enemy/enemy.hpp"

namespace fnad {
enum class Direction { up, down, right, left };

class Character final {
 private:
  Position position_;
  int life_points_;

 public:
  Character();

  bool checkContact(const Enemy&);
  void move(const Direction&);
};
}  // namespace fnad

#endif
