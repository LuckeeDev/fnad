#include <SFML/Graphics.hpp>

#include "../common/position.hpp"
#include "../enemy/enemy.hpp"

#ifndef CHARACTER_HPP
#define CHARACTER_HPP

namespace fnad {
class Character {
 private:
  Position position_;
  int life_points_;

 public:
  Character()
      : life_points_{3},
        position_{sf::Vector2f{0.f, 0.f}, Floor::underground} {};

  // TODO: add reference
  bool checkContact(const Enemy);
  void move(const sf::Vector2f);
};
}  // namespace fnad

#endif  // character_HPP
