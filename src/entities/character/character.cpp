#include "character.hpp"

#include "../../map/map.hpp"
#include "../enemy/enemy.hpp"

namespace fnad {
// Constructors
Character::Character(Map const& map, sf::Vector2f const& position, float speed)
    : Entity(map, position, speed), life_points_{3}, movement_{0.f, 0.f} {
  setFillColor(sf::Color::Blue);

  static_texture_.loadFromFile(
      "../../../assets/skins/character/character_static.png");
  dynamic_texture_.loadFromFile(
      "../../../assets/skins/character/character_dynamic.png");
}

Character::Character(Map const& map, sf::Vector2f const& position)
    : Character(map, position, 60.f) {}

// Functions
bool Character::checkContacts(std::vector<Enemy> const& enemies) {
  bool is_contact{false};

  for (auto const& enemy : enemies) {
    if (enemy.getStatus() == Status::infectious) {
      auto const& enemy_rect = enemy.getGlobalBounds();

      auto const intersect = getGlobalBounds().intersects(enemy_rect);

      if (intersect) {
        is_contact = true;

        if (last_hit_.getElapsedTime() >= min_elapsed_time) {
          life_points_ -= 1;
          last_hit_.restart();
        }
      }
    }
  }

  return is_contact;
}

int Character::getLifePoints() const { return life_points_; }

void Character::resetMovement() { movement_ = sf::Vector2f{0.f, 0.f}; }

void Character::addMovement(Direction const& dir) {
  switch (dir) {
    case Direction::up:
      movement_ += sf::Vector2f{0.f, -1.f};
      break;
    case Direction::down:
      movement_ += sf::Vector2f{0.f, 1.f};
      break;
    case Direction::left:
      movement_ += sf::Vector2f{-1.f, 0.f};
      break;
    case Direction::right:
      movement_ += sf::Vector2f{1.f, 0.f};
      break;
  }
}

void Character::applyMovement(sf::Time const& dt) {
  float const norm =
      std::sqrt(std::pow(movement_.x, 2.f) + std::pow(movement_.y, 2.f));
  auto const seconds = dt.asSeconds();

  if (norm > 0.f) {
    auto const ds = movement_ / norm * speed_ * seconds;

    safeMove(ds);
  }
}

bool Character::isVisible() const {
  auto last_hit_elapsed_time = last_hit_.getElapsedTime();
  if (life_points_ == DEFAULT_LIFE_POINTS) {
    return true;
  } else {
    return last_hit_elapsed_time >= min_elapsed_time ||
           last_hit_elapsed_time.asMilliseconds() % 200 < 100;
  }
}
}  // namespace fnad