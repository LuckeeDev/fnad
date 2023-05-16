#include "entity.hpp"

#include "../../map/map.hpp"

namespace fnad {
Entity::Entity(Map& map, sf::Vector2f position, float speed)
    : sf::RectangleShape(sf::Vector2f{10.f, 10.f}),
      map_ptr_{&map},
      room_ptr_{nullptr},
      floor_{map.getFloor()},
      speed_{speed} {
  setPosition(position);

  auto rooms = map.getRooms();
  for (auto& room : rooms) {
    if (room.contains(position)) {
      room_ptr_ = &room;
      break;
    }
  }

  if (room_ptr_ == nullptr) {
    throw std::invalid_argument("Cannot create an entity outside the map.");
  }
};

void Entity::setFloor(Map& map, sf::Vector2f position) {
  floor_ = map.getFloor();

  setPosition(position);

  auto rooms = map.getRooms();
  for (auto& room : rooms) {
    if (room.contains(position)) {
      room_ptr_ = &room;
      break;
    }
  }

  if (room_ptr_ == nullptr) {
    throw std::invalid_argument("Cannot put an entity outside the map.");
  }
}
void Entity::setSpeed(const float& speed) { speed_ = speed; }

Map const& Entity::getMap() const { return *map_ptr_; }

Room const& Entity::getRoom() const { return *room_ptr_; }

Floor Entity::getFloor() const { return floor_; }

float Entity::getSpeed() const { return speed_; }
}  // namespace fnad