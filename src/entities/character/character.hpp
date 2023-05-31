#ifndef CHARACTER_HPP
#define CHARACTER_HPP

#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/System/Vector2.hpp>

#include "../entity/entity.hpp"

namespace fnad {
int const DEFAULT_LIFE_POINTS{3};

class Enemy;

class Character final : public Entity {
 private:
  sf::Time const MIN_ELAPSED_TIME_{sf::seconds(3.f)};
  int life_points_;
  sf::Vector2f movement_;
  sf::Clock last_hit_;
  sf::Clock animation_clock_;
  Direction animation_direction_;
  sf::Texture static_texture_;
  sf::Texture dynamic_texture_;

 public:
  Character(Map const&, sf::Vector2f const&, float);
  Character(Map const&, sf::Vector2f const&);

  bool checkContacts(std::vector<Enemy> const&);

  void resetMovement();
  void addMovement(Direction const&);
  void applyMovement(sf::Time const&);

  void animate();

  int getLifePoints() const;

  bool shouldBeDrawn() const;
};
}  // namespace fnad

#endif
