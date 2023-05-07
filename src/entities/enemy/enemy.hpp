#ifndef ENEMY_HPP
#define ENEMY_HPP

#include "../entity/entity.hpp"

namespace fnad {
enum class Floor;
class Character;

enum class Status { susceptible, infectious, removed };

class Enemy final : public Entity {
 private:
  Status status_;

 public:
  Enemy(Status, Floor, sf::Vector2f, float);
  Enemy(Status, Floor, sf::Vector2f);
  Enemy(Status);
  Enemy();

  void setStatus(const Status&);

  Status getStatus() const;

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