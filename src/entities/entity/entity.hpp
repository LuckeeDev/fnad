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
 private:
  void handleWallCollision(Axis const&, float const&);

 protected:
  const Map* const map_ptr_;
  // Defined in pixels/second
  float speed_;

  Entity(Map const&, sf::Vector2f const&, float);

  void safeMove(sf::Vector2f const&);

 public:
  void setSpeed(float);

  float getSpeed() const;
};
}  // namespace fnad

#endif