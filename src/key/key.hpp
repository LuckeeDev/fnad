#ifndef KEY_HPP
#define KEY_HPP

#include <SFML/Graphics.hpp>

namespace fnad {
class Character;

class Key : public sf::RectangleShape {
 private:
  bool taken_;

 public:
  Key(sf::Vector2f const&, sf::Vector2f const&);

  void checkTaken(Character const&);
  bool getTaken() const;
};
}  // namespace fnad

#endif