#ifndef CHARACTER_HPP
#define CHARACTER_HPP

#include <SFML/Graphics.hpp>

#include "../entity/entity.hpp"

namespace fnad {
class Enemy;

enum class Direction { up, down, right, left };

class Character final : public Entity {
  using sf::RectangleShape::move;

 private:
  int life_points_;

 public:
  Character(Map const&, sf::Vector2f);

  bool checkContact(const Enemy&);
  void move(const Direction&, const sf::Time&);

  int getLifePoints() const;
};
}  // namespace fnad

#endif
