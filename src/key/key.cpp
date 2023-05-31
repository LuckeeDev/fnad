#include "key.hpp"

#include "../entities/character/character.hpp"

namespace fnad {
sf::Texture Key::texture_;
bool Key::textured_{false};

Key::Key(sf::Vector2f const& position, sf::Vector2f const& size)
    : sf::RectangleShape(size) {
  setPosition(position);
}

Key::Key(sf::Vector2f const& position, sf::Vector2f const& size,
         int const& key_index)
    : Key::Key(position, size) {
  auto const& texture_size = texture_.getSize();
  // assume keys are squares
  auto keys = static_cast<int>(texture_size.x / texture_size.y);
  sf::IntRect key_rect{texture_size.x * key_index, 0, texture_size.x,
                       texture_size.y};

  setTexture(&texture_);
  setTextureRect(key_rect);
}

bool Key::isTextured() { return textured_; }

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

void Key::loadTexture() {
  texture_.loadFromFile("assets/map/items/keys.png");
  textured_ = true;
}
}  // namespace fnad