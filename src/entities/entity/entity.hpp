#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <SFML/Graphics.hpp>

namespace fnad {
class Map;

enum class Direction { right, up, left, down };

struct Collision {
  bool x;
  bool y;
};

bool operator==(Collision const&, Collision const&);

class Entity : public sf::RectangleShape {
 protected:
  Map const& map_;

  // Defined in units/second
  float speed_;

 public:
  Entity(Map const&, sf::Vector2f const&, float);

  /**
   * Move the entity and account for the presence of walls.
   *
   * @param ds a vector representing the displacement
   * @return a Collision object indicating if any collision happened on the x or
   * y axis
   */
  Collision safeMove(sf::Vector2f const&);

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