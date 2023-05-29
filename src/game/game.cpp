#include "game.hpp"

#include <iostream>

namespace fnad {
Game::Game(sf::RenderWindow& window, sf::View& view, Character& character,
           Epidemic& epidemic, Map& map, Background const& background)
    : window_{window},
      view_{view},
      view_height_{view.getSize().y},
      character_{character},
      epidemic_{epidemic},
      map_{map},
      background_{background} {
  font_.loadFromFile("assets/fonts/PressStart2P-Regular.ttf");
}

void Game::printStory() {
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

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
      clock_.restart();
      break;
    }

    window_.clear(sf::Color::Black);

    sf::Text text("Press ENTER to play.", font_, 32.f);
    text.setPosition(50.f, 50.f);

    window_.draw(text);

    window_.display();
  }
}

void Game::run() {
  while (window_.isOpen()) {
    auto const& dt = clock_.restart();

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

    character_.applyMovement(dt);

    epidemic_.evolve(dt, character_);

    if (character_.getLifePoints() <= 0) {
      win_ = false;
      break;
    }

    map_.collectKeys(character_);

    if (map_.hasWon(character_)) {
      win_ = true;
      break;
    }

    // Set the view centered on the character
    view_.setCenter(character_.getPosition());
    window_.setView(view_);

    window_.clear(sf::Color::Black);

    window_.draw(background_);

    window_.draw(map_);

    window_.draw(epidemic_);

    window_.draw(character_);

    window_.display();
  }
}

void Game::end() {
  auto const window_size = static_cast<sf::Vector2f>(window_.getSize());
  view_.setSize(window_size);
  view_.setCenter(window_size / 2.f);

  window_.setView(view_);

  while (window_.isOpen()) {
    sf::Event event;

    while (window_.pollEvent(event)) {
      if (event.type == sf::Event::Closed) window_.close();

      if (event.type == sf::Event::Resized) {
        auto aspect_ratio = static_cast<float>(event.size.width) /
                            static_cast<float>(event.size.height);

        view_.setSize({aspect_ratio * view_height_, view_height_});

        window_.setView(view_);
      }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
      window_.close();
    }

    window_.clear(sf::Color::Black);

    sf::Text text;
    text.setFont(font_);
    text.setCharacterSize(32.f);

    if (win_) {
      text.setString("You won!\nPress ENTER to close.");
    } else {
      text.setString("You lost :(\nPress ENTER to close.");
    }

    text.setPosition(50.f, 50.f);

    window_.draw(text);

    window_.display();
  }
}
}  // namespace fnad