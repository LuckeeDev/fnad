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
   * Randomly move the enemy.
   *
   * @param dt sf::Time object representing how long the enemy should move for
   */
  void randomMove(sf::Time const&);

 public:
  /**
   * Create a new enemy.
   *
   * @param map the map used to check for wall collisions
   * @param position the starting position
   * @param status the initial status
   * @param speed the speed of the enemy
   */
  Enemy(Map const&, sf::Vector2f const&, Status const&, float const&);

  /**
   * Create a new enemy.
   *
   * @param map the map used to check for wall collisions
   * @param position the starting position
   * @param status the initial status
   */
  Enemy(Map const&, sf::Vector2f const&, Status const&);

  /**
   * Load the static texture shared among all enemies.
   */
  static void loadTexture();

  /**
   * @returns the status of the enemy
   */
  Status getStatus() const;

  /**
   * @param character A reference to the character that the enemy could see
   * @returns true if the enemy sees the character, false otherwise
   */
  bool sees(const Character& character) const;

  /**
   * @param dt Delta time object indicating how much time has passed since the
   * last render
   * @param character A reference to the character, used by an infectious
   * enemy
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

  /**
   * Set the new Texture to animate the movement of the enemy.
   */
  void animate();
};
}  // namespace fnad

#endif