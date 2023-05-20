#ifndef ENEMY_HPP
#define ENEMY_HPP

#include "../entity/entity.hpp"

namespace fnad {
class Character;

enum class Status { susceptible, infectious, removed };

class Enemy final : public Entity {
 private:
  Status status_;

 public:
  Enemy(Map const&, sf::Vector2f, Status, float);
  Enemy(Map const&, sf::Vector2f, Status);

  Status getStatus() const;

  bool sees(const Character&) const;

  /**
   * @param dt delta time object indicating how much time has passed since the
   * last render
   * @param character a reference to the character, used by an infectious
   * enemy
   */
  void evolve(const sf::Time& dt, const Character& character);

  void infect();
  void remove();
};
}  // namespace fnad

#endif