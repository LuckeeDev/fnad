#ifndef CHARACTER_HPP
#define CHARACTER_HPP

#include <SFML/Graphics.hpp>

#include "../../common/position.hpp"
#include "../enemy/enemy.hpp"
#include "../entity/entity.hpp"

namespace fnad {
enum class Direction { up, down, right, left };

class Character final : public Entity {
 private:
  int life_points_;

 public:
  Character();

  bool checkContact(const Enemy&);
  void move(const Direction&, const sf::Time&);
};
}  // namespace fnad

#endif
