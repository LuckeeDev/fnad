#include "game.hpp"

#include <string>

#include "../key/key.hpp"

namespace fnad {
// Constructors
Game::Game(tmx::Map const& tiled_map)
    : window_{sf::VideoMode::getDesktopMode(), "Five nights at DIFA"},
      map_{tiled_map},
      background_{tiled_map},
      character_{map_, {2650.f, 1000.f}} {
  window_.setFramerateLimit(60);

  music_.openFromFile("assets/music/music.ogg");

  font_.loadFromFile("assets/fonts/PressStart2P-Regular.ttf");

  Enemy::loadTexture();
  Key::loadTexture();
}

// Public methods

void Game::printStory() {
  text_.setPosition(50.f, 50.f);
  text_.setLineSpacing(1.5f);

  window_.setView(view_);

  while (window_.isOpen()) {
    while (window_.pollEvent(event_)) {
      if (event_.type == sf::Event::Closed) window_.close();

      if (event_.type == sf::Event::Resized) {
        const sf::Vector2f new_window_size{
            static_cast<float>(event_.size.width),
            static_cast<float>(event_.size.height)};

        view_.setSize(new_window_size);
        view_.setCenter(new_window_size / 2.f);

        window_.setView(view_);
      }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)) {
      level_ = 1;
      epidemic_.resetSIRState({5, 1, 0}, map_);
      break;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)) {
      level_ = 2;
      epidemic_.resetSIRState({20, 1, 0}, map_);
      break;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3)) {
      level_ = 3;
      epidemic_.resetSIRState({40, 1, 0}, map_);
      break;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4)) {
      level_ = 4;
      epidemic_.resetSIRState({100, 1, 0}, map_);
      break;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num5)) {
      level_ = 5;
      epidemic_.resetSIRState({200, 1, 0}, map_);
      break;
    }

    window_.clear(sf::Color::Black);

    window_.draw(text_);

    window_.display();
  }
}

void Game::run() {
  music_.play();

  auto const window_size = static_cast<sf::Vector2f>(window_.getSize());
  auto const aspect_ratio = window_size.x / window_size.y;

  view_.setSize({aspect_ratio * game_view_height, game_view_height});
  view_.setCenter(character_.getPosition());

  window_.setView(view_);

  text_.setScale({0.2f, 0.2f});
  text_.setLineSpacing(1.3f);

  clock_.restart();

  while (window_.isOpen()) {
    auto const& dt = clock_.restart();

    auto const& enemies = epidemic_.getEnemies();

    character_.checkContacts(enemies);

    if (character_.getLifePoints() <= 0) {
      win_ = false;
      break;
    }

    while (window_.pollEvent(event_)) {
      if (event_.type == sf::Event::Closed) window_.close();

      if (event_.type == sf::Event::Resized) {
        auto const new_aspect_ratio = static_cast<float>(event_.size.width) /
                                      static_cast<float>(event_.size.height);

        view_.setSize({new_aspect_ratio * game_view_height, game_view_height});
      }
    }

    character_.resetMovement();

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
      character_.addMovement(Direction::left);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
      character_.addMovement(Direction::right);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) ||
        // On Italian keyboards, this corresponds to the W key
        sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) {
      character_.addMovement(Direction::up);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
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

    auto const text_position = window_.mapPixelToCoords({20, 20});

    text_.setPosition(text_position.x, text_position.y);
    text_.setString(
        "Level " + std::to_string(level_) +
        "\nLife points: " + std::to_string(character_.getLifePoints()) +
        "\nKeys collected: " + std::to_string(map_.countTakenKeys()));

    window_.draw(text_);

    window_.display();
  }
}

void Game::end() {
  music_.stop();

  text_.setPosition(50.f, 50.f);
  text_.setLineSpacing(1.5f);

  auto const window_size = static_cast<sf::Vector2f>(window_.getSize());
  view_.setSize(window_size);
  view_.setCenter(window_size / 2.f);

  window_.setView(view_);

  while (window_.isOpen()) {
    while (window_.pollEvent(event_)) {
      if (event_.type == sf::Event::Closed) window_.close();

      if (event_.type == sf::Event::Resized) {
        const sf::Vector2f new_window_size{
            static_cast<float>(event_.size.width),
            static_cast<float>(event_.size.height)};

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