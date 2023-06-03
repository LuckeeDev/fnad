#include "game.hpp"

#include <fstream>
#include <string>

#include "../key/key.hpp"

namespace fnad {
// Constructors

Game::Game(tmx::Map const& tiled_map)
    : window_{sf::VideoMode::getDesktopMode(), "Five nights at DIFA"},
      text_{"", font_, 32},
      map_{tiled_map},
      background_{tiled_map},
      character_{map_, {2650.f, 1000.f}},
      GAME_VIEW_HEIGHT_{400.f} {
  window_.setFramerateLimit(60);

  text_.setFillColor(sf::Color::White);
  text_.setOutlineThickness(2.f);
  text_.setOutlineColor(sf::Color::Black);

  std::ifstream story_input{"assets/text/story.txt"};
  std::string text_string;
  std::string line;

  auto max_line_lenght = text_string.size();

  int lines_count{};

  while (std::getline(story_input, line)) {
    text_string += line + '\n';

    auto line_lenght = line.size();
    if (line_lenght > max_line_lenght) {
      max_line_lenght = line_lenght;
    }

    lines_count++;
  }

  auto const character_size = static_cast<float>(text_.getCharacterSize());

  auto const text_scale_x =
      (static_cast<float>(window_.getSize().x) - 100.f) /
      (character_size * static_cast<float>(max_line_lenght));

  auto const text_scale_y = (2.f / character_size) *
                            (static_cast<float>(window_.getSize().y) - 150.f) /
                            (3.f * static_cast<float>(lines_count) - 1.f);

  text_.setString(text_string);

  if (text_scale_x < text_scale_y) {
    text_.setScale(text_scale_x, text_scale_x);
  } else {
    text_.setScale(text_scale_y, text_scale_y);
  }

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
      if (event_.type == sf::Event::Closed) {
        window_.close();
      }

      if (event_.type == sf::Event::Resized) {
        sf::Vector2f const new_window_size{
            static_cast<float>(event_.size.width),
            static_cast<float>(event_.size.height)};

        view_.setSize(new_window_size);
        view_.setCenter(new_window_size / 2.f);

        window_.setView(view_);
      }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad1)) {
      level_ = 1;
      epidemic_.resetSIRState({5, 1, 0}, map_);
      time_limit_ = sf::seconds(600.f);
      character_.setLifePoints(3);
      break;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad2)) {
      level_ = 2;
      epidemic_.resetSIRState({20, 1, 0}, map_);
      time_limit_ = sf::seconds(540.f);
      character_.setLifePoints(3);
      break;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad3)) {
      level_ = 3;
      epidemic_.resetSIRState({40, 1, 0}, map_);
      time_limit_ = sf::seconds(480.f);
      character_.setLifePoints(4);
      break;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad4)) {
      level_ = 4;
      epidemic_.resetSIRState({100, 1, 0}, map_);
      time_limit_ = sf::seconds(420.f);
      character_.setLifePoints(4);
      break;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num5) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad5)) {
      level_ = 5;
      epidemic_.resetSIRState({200, 1, 0}, map_);
      time_limit_ = sf::seconds(360.f);
      character_.setLifePoints(5);
      break;
    }

    window_.clear(sf::Color::Black);

    window_.draw(text_);

    window_.display();
  }
}

void Game::run() {
  auto const window_size = static_cast<sf::Vector2f>(window_.getSize());
  auto const aspect_ratio = window_size.x / window_size.y;

  view_.setSize({aspect_ratio * GAME_VIEW_HEIGHT_, GAME_VIEW_HEIGHT_});
  view_.setCenter(character_.getPosition());

  window_.setView(view_);

  text_.setScale({0.2f, 0.2f});
  text_.setLineSpacing(1.3f);

  game_clock_.restart();
  match_timer_.restart();

  while (window_.isOpen()) {
    auto const dt = game_clock_.restart();

    auto const& enemies = epidemic_.getEnemies();

    character_.checkContacts(enemies);

    if (character_.getLifePoints() <= 0 ||
        match_timer_.getElapsedTime() >= time_limit_) {
      win_ = false;
      break;
    }

    while (window_.pollEvent(event_)) {
      if (event_.type == sf::Event::Closed) {
        window_.close();
      }

      if (event_.type == sf::Event::Resized) {
        auto const new_aspect_ratio = static_cast<float>(event_.size.width) /
                                      static_cast<float>(event_.size.height);

        view_.setSize(
            {new_aspect_ratio * GAME_VIEW_HEIGHT_, GAME_VIEW_HEIGHT_});
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
        // On some Italian keyboards, this corresponds to the W key
        sf::Keyboard::isKeyPressed(sf::Keyboard::Z) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
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
        "Livello " + std::to_string(level_) +
        "\nPunti vita: " + std::to_string(character_.getLifePoints()) +
        "\nChiavi raccolte: " + std::to_string(map_.countTakenKeys()) +
        "\nTempo rimasto: " +
        std::to_string(static_cast<int>(std::ceil(
            (time_limit_ - match_timer_.getElapsedTime()).asSeconds()))) +
        "s");

    window_.draw(text_);

    window_.display();
  }
}

void Game::end() {
  text_.setPosition(50.f, 50.f);
  text_.setLineSpacing(1.5f);
  text_.setScale({0.8f, 0.8f});

  auto const window_size = static_cast<sf::Vector2f>(window_.getSize());
  view_.setSize(window_size);
  view_.setCenter(window_size / 2.f);

  window_.setView(view_);

  while (window_.isOpen()) {
    while (window_.pollEvent(event_)) {
      if (event_.type == sf::Event::Closed) {
        window_.close();
      }

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

    if (win_) {
      text_.setString("Hai vinto!\nPremi INVIO per uscire.");
    } else {
      text_.setString("Hai perso :(\nPremi INVIO per uscire.");
    }

    window_.draw(text_);

    window_.display();
  }
}
}  // namespace fnad