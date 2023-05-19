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

    auto const& dt = clock_.restart();

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
      character_.move(Direction::left, dt);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
      character_.move(Direction::right, dt);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
      character_.move(Direction::up, dt);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
      character_.move(Direction::down, dt);
    }

    // Set the view centered on the character
    view_.setCenter(character_.getPosition() + character_.getSize() / 2.f);
    window_.setView(view_);

    window_.clear(sf::Color::Black);

    window_.draw(background_);

    epidemic_.evolve(dt);
    window_.draw(epidemic_);

    window_.draw(character_);

    window_.display();
  }
}
}  // namespace fnad