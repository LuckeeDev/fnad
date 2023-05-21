#ifndef CHARACTER_HPP
#define CHARACTER_HPP

#include <SFML/Graphics.hpp>

#include "../entity/entity.hpp"

namespace fnad {
class Enemy;

enum class Direction { up, down, right, left };

class Character final : public Entity {
 private:
  int life_points_;
  sf::Vector2f movement_;

 public:
  Character(Map const&, sf::Vector2f, float);
  Character(Map const&, sf::Vector2f);

  bool checkContact(const Enemy&);

  void resetMovement();
  void addMovement(Direction const&);
  void applyMovement(sf::Time const&);

  int getLifePoints() const;
};
}  // namespace fnad

#endif
