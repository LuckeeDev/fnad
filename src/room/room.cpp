#include "room.hpp"

namespace fnad {
Room::Room(sf::Vector2f const& position, sf::Vector2f const& size,
           Floor const& floor)
    : sf::FloatRect(position, size), floor_{floor} {}
}  // namespace fnad