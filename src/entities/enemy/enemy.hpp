#ifndef ENEMY_HPP
#define ENEMY_HPP

#include "../entity/entity.hpp"

namespace fnad {
class Character;

enum class Status { susceptible, infectious, removed };

class Enemy final : public Entity {
 private:
  Status status_;

  sf::Vector2f direction_;

  sf::Clock clock_;

  sf::Time time_limit_;

  std::default_random_engine eng_;

  std::uniform_real_distribution<float> time_dist_;

  std::uniform_real_distribution<float> direction_dist_;

  Direction animation_direction_;
  sf::Clock animation_clock_;
  static sf::Texture dynamic_texture_;

  /**
   * A function that randomly moves the enemy.
   */
  void randomMove(sf::Time const&);

 public:
  Enemy(Map const&, sf::Vector2f const&, Status const&, float const&);
  Enemy(Map const&, sf::Vector2f const&, Status const&);

  static void loadTexture();

  /**
   * @returns the status of the enemy.
   */
  Status getStatus() const;

  /**
   * @param character A reference to the character that the enemy could see.
   * @returns true if the enemy sees the character, false otherwise.
   */
  bool sees(const Character& character) const;

  /**
   * @param dt Delta time object indicating how much time has passed since the
   * last render.
   * @param character A reference to the character, used by an infectious
   * enemy.
   */
  void evolve(const sf::Time& dt, const Character& character);

  /**
   * A function that turns the status of the enemy on which is called into
   * "infectious". It can be called only on enemies whose status is
   * "susceptible".
   */
  void infect();

  /**
   * A function that turns the status of the enemy on which is called into
   * "removed". It can be called only on enemies whose status is
   * "infectious".
   */
  void remove();
};
}  // namespace fnad

#endif