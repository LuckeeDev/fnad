#ifndef CHARACTER_HPP
#define CHARACTER_HPP

#include <SFML/Graphics.hpp>

#include "../../common/floor.hpp"
#include "../enemy/enemy.hpp"
#include "../entity/entity.hpp"

namespace fnad {
enum class Direction { up, down, right, left };

class Character final : public Entity {
  using sf::RectangleShape::move;

 private:
  int life_points_;

 public:
  Character();

  bool checkContact(const Enemy&);
  void move(const Direction&, const sf::Time&);

  int getLifePoints() const;
};
}  // namespace fnad

#endif
