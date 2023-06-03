#ifndef GAME_HPP
#define GAME_HPP

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

  sf::Clock game_clock_;
  sf::Font font_;

  sf::RenderWindow window_;
  sf::View view_;
  sf::Event event_;

  sf::Text text_;

  sf::Clock match_timer_;
  sf::Time time_limit_;

  // Game objects

  Map map_;
  Background background_;
  Character character_;
  Epidemic epidemic_;

  float const GAME_VIEW_HEIGHT_;

  bool win_;
  int level_;

  /**
   * Read player input to set level data.
   */
  void chooseLevel();

 public:
  /**
   * Create a new game instance from a Tiled map.
   *
   * @param tiled_map the game map
   */
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