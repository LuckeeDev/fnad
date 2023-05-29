#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>

#include "../background/background.hpp"
#include "../entities/character/character.hpp"
#include "../epidemic/epidemic.hpp"
#include "../map/map.hpp"

namespace fnad {
class Game final {
 private:
  sf::Clock clock_;
  sf::RenderWindow& window_;
  sf::View& view_;
  const float view_height_;

  Character& character_;
  Epidemic& epidemic_;
  Map& map_;
  Background const& background_;

  sf::Font font_;

  bool win_{false};

 public:
  Game(sf::RenderWindow&, sf::View&, Character&, Epidemic&, Map&,
       Background const&);

  void printStory();

  void run();

  void end();
};
}  // namespace fnad

#endif