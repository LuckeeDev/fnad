#include "spawner.hpp"

namespace fnad {
Spawner::Spawner(sf::Vector2f position, sf::Vector2f size)
    : sf::FloatRect(position, size),
      eng_((std::random_device())()),
      x_dist_(position.x + 5.f, position.x + size.x - 5.f),
      y_dist_(position.y + 5.f, position.y + size.y - 5.f) {}

float Spawner::getArea() const { return width * height; }

sf::Vector2f Spawner::getSpawnPoint() {
  auto x = x_dist_(eng_);
  auto y = y_dist_(eng_);

  return sf::Vector2f(x, y);
}
}  // namespace fnad