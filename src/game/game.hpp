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
  sf::RenderWindow& window_;
  sf::View& view_;

  Character& character_;
  Epidemic& epidemic_;
  Map const& map_;
  Background& background_;

 public:
  Game(sf::RenderWindow&, sf::View&, Character&, Epidemic&, Map&, Background&);

  void run() const;
};
}  // namespace fnad

#endif