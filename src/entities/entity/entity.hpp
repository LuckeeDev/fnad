#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <SFML/Graphics.hpp>

#include "../../room/room.hpp"

namespace fnad {
class Map;
enum class Floor;

class Entity : public sf::RectangleShape {
 protected:
  Map* map_ptr_;
  Room* room_ptr_;
  Floor floor_;
  // Defined in pixels/second
  float speed_;

  Entity(Map&, sf::Vector2f, float);

 public:
  void setFloor(Map&, sf::Vector2f);
  void setSpeed(const float&);

  Map const& getMap() const;
  Room const& getRoom() const;
  Floor getFloor() const;
  float getSpeed() const;
};
}  // namespace fnad

#endif