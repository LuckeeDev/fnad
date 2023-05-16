#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>

#include "../map/map.hpp"

namespace fnad {
class Game final {
 private:
  sf::RenderWindow* window_;
  sf::View* view_;

  Character* character_;
  Epidemic* epidemic_;
  Map* map_;

  Game(sf::RenderWindow*, sf::View*, Character*, Epidemic*, Map*);

 public:
  ~Game();

  void run() const;

  static Game create();
};
}  // namespace fnad

#endif