#include "game.hpp"

namespace fnad {
Game::Game(sf::RenderWindow& window, sf::View& view, Character& character,
           Epidemic& epidemic, Map const& map, Background const& background)
    : window_{window},
      view_{view},
      view_height_{view.getSize().y},
      character_{character},
      epidemic_{epidemic},
      map_{map},
      background_{background} {}

void Game::printStory() const {}

void Game::run() {
  while (window_.isOpen()) {
    sf::Event event;

    while (window_.pollEvent(event)) {
      if (event.type == sf::Event::Closed) window_.close();

      if (event.type == sf::Event::Resized) {
        auto aspect_ratio = static_cast<float>(event.size.width) /
                            static_cast<float>(event.size.height);

        view_.setSize({aspect_ratio * view_height_, view_height_});
      }
    }

    character_.resetMovement();

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
      character_.addMovement(Direction::left);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
      character_.addMovement(Direction::right);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
      character_.addMovement(Direction::up);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
      character_.addMovement(Direction::down);
    }

    auto const& dt = clock_.restart();

    character_.applyMovement(dt);

    epidemic_.evolve(dt, character_);

    // Set the view centered on the character
    view_.setCenter(character_.getPosition());
    window_.setView(view_);

    window_.clear(sf::Color::Black);

    window_.draw(background_);

    window_.draw(epidemic_);

    window_.draw(character_);

    window_.display();
  }
}
}  // namespace fnad