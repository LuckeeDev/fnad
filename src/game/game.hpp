#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <tmxlite/Map.hpp>

#include "../background/background.hpp"
#include "../entities/character/character.hpp"
#include "../epidemic/epidemic.hpp"
#include "../map/map.hpp"

namespace fnad {
class Game final {
 private:
  // SFML objects

  sf::Clock clock_;
  sf::Font font_;

  sf::RenderWindow window_;
  sf::View view_;
  sf::Event event_;

  sf::Music music_;

  sf::Text text_{
      "Press a number to choose the level.\nLevel [1]\nLevel [2]\nLevel "
      "[3]\nLevel [4]\nLevel [5]",
      font_, 32};

  // Game objects

  Map map_;
  Background const background_;
  Character character_;
  Epidemic epidemic_;

  const float game_view_height{400.f};

  bool win_{false};
  int level_;

 public:
  Game(tmx::Map const&);

  /**
   * Print the background story of the game. Wait for the player to press a key
   * to start the game.
   */
  void printStory();

  /**
   * Run the game logic.
   */
  void run();

  /**
   * Show the result of the game. Wait for the player to press a key to close
   * the window.
   */
  void end();
};
}  // namespace fnad

#endif