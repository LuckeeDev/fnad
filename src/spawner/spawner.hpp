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

  /**
   * @return the area of the spawner
   */
  double getArea() const;

  /**
   * @return a random spawn point inside the spawner.
   */
  sf::Vector2f getSpawnPoint();
};
}  // namespace fnad

#endif