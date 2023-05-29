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
  sf::Clock clock_;
  sf::Font font_;

  sf::RenderWindow window_;
  sf::View view_;
  Map map_;
  Background const background_;
  Character character_;
  Epidemic epidemic_;

  const float default_view_height_;

  bool win_{false};

 public:
  Game(tmx::Map const&, std::vector<sf::Texture> const&);

  void printStory();

  void run();

  void end();
};
}  // namespace fnad

#endif