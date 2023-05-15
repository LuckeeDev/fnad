#ifndef ROOM_HPP
#define ROOM_HPP
#include <SFML/Graphics.hpp>

#include "../common/floor.hpp"

namespace fnad {
class Room : public sf::FloatRect {
 private:
  sf::Vector2f position_;
  sf::Vector2f size_;
  Floor floor_;

 public:
  Room(sf::Vector2f const&, sf::Vector2f const&, Floor const&);
};
}  // namespace fnad
#endif