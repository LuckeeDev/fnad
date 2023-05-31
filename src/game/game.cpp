#include "game.hpp"

#include "../key/key.hpp"

namespace fnad {
Game::Game(tmx::Map const& tiled_map)
    : window_{sf::VideoMode::getDesktopMode(), "Five nights at DIFA"},
      view_{},
      map_{tiled_map},
      background_{tiled_map},
      character_{map_, {0.f, 0.f}},
      game_view_height{200.f} {
  window_.setFramerateLimit(60);

  font_.loadFromFile("assets/fonts/PressStart2P-Regular.ttf");

  Enemy::loadTexture();
  Key::loadTexture();
}

void Game::printStory() {
  window_.setView(view_);

  while (window_.isOpen()) {
    sf::Event event;

    while (window_.pollEvent(event)) {
      if (event.type == sf::Event::Closed) window_.close();

      if (event.type == sf::Event::Resized) {
        const sf::Vector2f new_window_size{
            static_cast<float>(event.size.width),
            static_cast<float>(event.size.height)};

        view_.setSize(new_window_size);
        view_.setCenter(new_window_size / 2.f);

        window_.setView(view_);
      }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
      epidemic_.resetSIRState({99, 1, 0}, map_);
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
  auto const window_size = static_cast<sf::Vector2f>(window_.getSize());
  auto const aspect_ratio = window_size.x / window_size.y;

  view_.setSize({aspect_ratio * game_view_height, game_view_height});
  view_.setCenter(character_.getPosition());

  window_.setView(view_);

  clock_.restart();

  while (window_.isOpen()) {
    auto const& dt = clock_.restart();

    auto const& enemies = epidemic_.getEnemies();

    character_.checkContacts(enemies);

    if (character_.getLifePoints() <= 0) {
      win_ = false;
      break;
    }

    sf::Event event;

    while (window_.pollEvent(event)) {
      if (event.type == sf::Event::Closed) window_.close();

      if (event.type == sf::Event::Resized) {
        auto const new_aspect_ratio = static_cast<float>(event.size.width) /
                                      static_cast<float>(event.size.height);

        view_.setSize({new_aspect_ratio * game_view_height, game_view_height});
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

    map_.collectKeys(character_);

    if (map_.hasWon(character_)) {
      win_ = true;
      break;
    }

    // Set the view centered on the character
    view_.setCenter(character_.getPosition());
    window_.setView(view_);

    character_.animate();

    window_.clear(sf::Color::Black);

    window_.draw(background_);

    window_.draw(map_);

    window_.draw(epidemic_);

    if (character_.shouldBeDrawn()) {
      window_.draw(character_);
    }

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
        const sf::Vector2f new_window_size{
            static_cast<float>(event.size.width),
            static_cast<float>(event.size.height)};

        view_.setSize(new_window_size);
        view_.setCenter(new_window_size / 2.f);

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