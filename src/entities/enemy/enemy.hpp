#ifndef ENEMY_HPP
#define ENEMY_HPP

#include "../../common/position.hpp"
#include "../character/character.hpp"
#include "../entity/entity.hpp"

namespace fnad {
enum class Status { susceptible, infectious, removed };

class Enemy final : public Entity {
 private:
  Status status_;

 public:
  Enemy(Status status, Position position, float speed);
  Enemy(Status status, Position position);
  Enemy(Status status);
  Enemy();

  Status status() const;

  /**
   * @param dt delta time object indicating how much time has passed since the
   * last render
   * @param character a reference to the character, used by an infectious
   * enemy
   */
  void evolve(const sf::Time& dt, const Character& character);

  void infect();
};
}  // namespace fnad

#endif