#include "room.hpp"

namespace fnad {
Room::Room(sf::Vector2f const& position, sf::Vector2f const& size)
    : sf::FloatRect(position, size) {}
}  // namespace fnad