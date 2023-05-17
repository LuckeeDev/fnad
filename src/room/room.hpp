#ifndef ROOM_HPP
#define ROOM_HPP
#include <SFML/Graphics.hpp>

namespace fnad {
class Room : public sf::FloatRect {
 private:
 public:
  Room(sf::Vector2f const&, sf::Vector2f const&);
};
}  // namespace fnad
#endif