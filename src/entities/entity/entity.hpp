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

class Entity : public sf::RectangleShape {
 protected:
  const Map* map_ptr_;
  // Defined in pixels/second
  float speed_;

  Entity(Map const&, sf::Vector2f, float);

  bool isWallCollision() const;

  void handleWallCollision(Axis const&, float const&);

 public:
  void setSpeed(float);

  float getSpeed() const;
};
}  // namespace fnad

#endif