#ifndef SPAWNER_HPP
#define SPAWNER_HPP

#include <SFML/Graphics.hpp>
#include <random>

namespace fnad {
class Spawner final : public sf::FloatRect {
 private:
  std::default_random_engine eng_;
  std::uniform_real_distribution<float> x_dist_;
  std::uniform_real_distribution<float> y_dist_;

 public:
  /**
   * Construct a spawner from its position and its size.
   *
   * @param position the position of the spawner
   * @param size the size of the spawner
   */
  Spawner(sf::Vector2f const&, sf::Vector2f const&);

  /**
   * @return the area of the spawner
   */
  double getArea() const;

  /**
   * @return a random spawn point inside the spawner
   */
  sf::Vector2f getSpawnPoint();
};
}  // namespace fnad

#endif