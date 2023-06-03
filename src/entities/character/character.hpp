#ifndef CHARACTER_HPP
#define CHARACTER_HPP

#include <SFML/System.hpp>

#include "../entity/entity.hpp"

namespace fnad {
class Enemy;

class Character final : public Entity {
 private:
  int initial_life_points_;
  int life_points_;

  sf::Vector2f movement_;

  sf::Time const MIN_HIT_TIME_{sf::seconds(3.f)};
  sf::Clock last_hit_;

  sf::Clock animation_clock_;
  Direction animation_direction_;
  sf::Texture static_texture_;
  sf::Texture dynamic_texture_;

 public:
  /**
   * Create a new character.
   *
   * @param map the map used to check for wall collisions
   * @param position the starting position
   * @param speed the speed of the character
   */
  Character(Map const&, sf::Vector2f const&, float);

  /**
   * Create a new character.
   *
   * @param map the map used to check for wall collisions
   * @param position the starting position
   */
  Character(Map const&, sf::Vector2f const&);

  /**
   * Check for contacts with a vector of enemies. If a contact is detected,
   * decrease life points.
   *
   * @param enemies a vector of enemies. They can be of any SIR state
   */
  bool checkContacts(std::vector<Enemy> const&);

  /**
   * Reset the movement vector to {0, 0}. Should be used at the begininning of
   * each frame.
   */
  void resetMovement();

  /**
   * Add a direction movement to the movement vector. Should be used each frame
   * in combination with key codes.
   *
   * @param direction one of the four directions
   */
  void addMovement(Direction const&);

  /**
   * Calculate the movement of the character based on the elapsed time and the
   * movement vector. It accounts for wall collisions as well.
   *
   * @param dt the elapsed time
   */
  void applyMovement(sf::Time const&);

  /**
   * Set the new Texture to animate the movement of the character.
   */
  void animate();

  /**
   * @return the current life points
   */
  int getLifePoints() const;

  /**
   * Set the current and initial life points to the passed value.
   *
   * @param life_points new life points
   */
  void setLifePoints(int);

  /**
   * Used to show a flickering image of the character when not enough time has
   * passed since the last hit from an enemy.
   *
   * @return a boolean indicating whether the character should be drawn to the
   * screen or not
   */
  bool shouldBeDrawn() const;
};
}  // namespace fnad

#endif
