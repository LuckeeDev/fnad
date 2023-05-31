#include "game.hpp"

#include <string>

namespace fnad {
Game::Game(tmx::Map const& tiled_map,
           std::vector<sf::Texture> const& key_textures)
    : window_{sf::VideoMode::getDesktopMode(), "Five nights at DIFA"},
      map_{tiled_map, key_textures},
      background_{tiled_map},
      character_{map_, {0.f, 0.f}} {
  window_.setFramerateLimit(60);

  font_.loadFromFile("assets/fonts/PressStart2P-Regular.ttf");

  info_life_.setFillColor(sf::Color::White);
  info_life_.setScale({0.25f, 0.25f});
  info_keys_.setFillColor(sf::Color::White);
  info_keys_.setScale({0.25f, 0.25f});
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
  music_.openFromFile("assets/music/music.ogg");

  Enemy::loadTexture();

  music_.play();

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

    auto const text_position = window_.mapPixelToCoords({0, 0});

    info_life_.setPosition(text_position.x, text_position.y);
    info_life_.setString("Life points: " +
                         std::to_string(character_.getLifePoints()));

    window_.draw(info_life_);

    info_keys_.setPosition(text_position.x, text_position.y + 12.f);
    info_keys_.setString("Keys collected: " +
                         std::to_string(map_.countTakenKeys()));

    window_.draw(info_keys_);

    window_.display();
  }
}

void Game::end() {
  music_.stop();

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