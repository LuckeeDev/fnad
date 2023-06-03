#include "spawner.hpp"

namespace fnad {
Spawner::Spawner(sf::Vector2f const& position, sf::Vector2f const& size)
    : sf::FloatRect{position, size},
      eng_{std::random_device{}()},
      // Create enemy inside the walls around the spawner
      x_dist_{position.x + 16.f, position.x + size.x - 16.f},
      y_dist_{position.y + 24.f, position.y + size.y - 24.f} {}

double Spawner::getArea() const {
  return static_cast<double>(width) * static_cast<double>(height);
}

sf::Vector2f Spawner::getSpawnPoint() {
  auto const x = x_dist_(eng_);
  auto const y = y_dist_(eng_);

  return sf::Vector2f{x, y};
}
}  // namespace fnad