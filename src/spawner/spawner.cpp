#include "spawner.hpp"

namespace fnad {
Spawner::Spawner(sf::Vector2f position, sf::Vector2f size)
    : sf::FloatRect(position, size),
      gen_((std::random_device())()),
      x_dist_(position.x, position.x + size.x),
      y_dist_(position.y, position.y + size.y) {}
}  // namespace fnad