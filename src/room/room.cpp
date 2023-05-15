#include "room.hpp"

namespace fnad {
Room::Room(sf::Vector2f const& position, sf::Vector2f const& size,
           Floor const& floor)
    : position_{position}, size_{size}, floor_{floor} {}
}  // namespace fnad