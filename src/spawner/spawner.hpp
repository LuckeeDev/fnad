#ifndef SPAWNER_HPP
#define SPAWNER_HPP

#include <SFML/Graphics/Rect.hpp>
#include <random>

namespace fnad {
class Spawner : public sf::FloatRect {
 private:
  std::default_random_engine eng_;
  std::uniform_real_distribution<float> x_dist_;
  std::uniform_real_distribution<float> y_dist_;

 public:
  Spawner(sf::Vector2f, sf::Vector2f);

  float getArea() const;

  sf::Vector2f getSpawnPoint();
};
}  // namespace fnad

#endif