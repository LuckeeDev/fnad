#include "key.hpp"

#include "../entities/character/character.hpp"

namespace fnad {
sf::Texture Key::texture_;

Key::Key(sf::Vector2f const& position, sf::Vector2f const& size)
    : sf::RectangleShape(size) {
  setPosition(position);
}

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

void Key::loadTexture() { texture_.loadFromFile("assets/map/items/keys.png"); }
}  // namespace fnad