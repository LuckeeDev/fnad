#include "key.hpp"

#include "../entities/character/character.hpp"

namespace fnad {
// Static members

sf::Texture Key::texture_;

// Constructors

Key::Key(sf::Vector2f const& position, sf::Vector2f const& size, int key_index)
    : sf::RectangleShape{size}, taken_{false} {
  setPosition(position);
  sf::IntRect key_rect{32 * key_index, 0, 32, 32};

  setTexture(&texture_);
  setTextureRect(key_rect);
}

// Public methods

void Key::loadTexture() { texture_.loadFromFile("assets/map/items/keys.png"); }

void Key::checkTaken(Character const& character) {
  if (taken_ == false) {
    auto const& key_rect = getGlobalBounds();
    auto const& character_rect = character.getGlobalBounds();

    if (key_rect.intersects(character_rect)) {
      taken_ = true;
    }
  }
}

bool Key::getTaken() const { return taken_; }
}  // namespace fnad