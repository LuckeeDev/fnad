#include "game.hpp"

namespace fnad {
Game::Game(sf::RenderWindow& window, sf::View& view, Character& character,
           Epidemic& epidemic, Map& map)
    : window_{window},
      view_{view},
      character_{character},
      epidemic_{epidemic},
      map_{map} {}

void Game::run() const {
  while (window_.isOpen()) {
    sf::Event event;
    while (window_.pollEvent(event)) {
      if (event.type == sf::Event::Closed) window_.close();
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
      view_.move(-5.f, 0.f);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
      view_.move(5.f, 0.f);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
      view_.move(0.f, -5.f);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
      view_.move(0.f, 5.f);
    }

    window_.clear(sf::Color::Black);

    window_.setView(view_);

    window_.draw(map_);

    window_.display();
  }
}
}  // namespace fnad