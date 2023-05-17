#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <SFML/Graphics.hpp>

#include "../../room/room.hpp"

namespace fnad {
class Map;

class Entity : public sf::RectangleShape {
 protected:
  const Map* map_ptr_;
  Room* room_ptr_;
  // Defined in pixels/second
  float speed_;

  Entity(Map const&, sf::Vector2f, float);

 public:
  void setSpeed(float);

  Room const& getRoom() const;
  float getSpeed() const;
};
}  // namespace fnad

#endif