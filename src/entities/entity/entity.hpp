#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <SFML/Graphics.hpp>

#include "../../map/map.hpp"

namespace fnad {
class Map;

enum class Axis {
  x,
  y,
};

enum class Direction { right, up, left, down };

class Entity : public sf::RectangleShape {
 private:
  void handleWallCollision(Axis const&, float const&);

 protected:
  Map const& map_;

  // Defined in units/second
  float speed_;

  Entity(Map const&, sf::Vector2f const&, float);

  /**
   * Move the entity and account for the presence of walls.
   */
  void safeMove(sf::Vector2f const&);

 public:
  /**
   * Set the speed of the entity.
   *
   * @param speed the new speed
   */
  void setSpeed(float);

  /**
   * @return the current speed
   */
  float getSpeed() const;
};
}  // namespace fnad

#endif