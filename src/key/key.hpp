#ifndef KEY_HPP
#define KEY_HPP

#include <SFML/Graphics.hpp>

namespace fnad {
class Character;

class Key : public sf::RectangleShape {
 private:
  static sf::Texture texture_;
  static bool textured_;
  bool taken_{false};

 public:
  static bool isTextured();

  /**
   * Construct a Key object.
   *
   * @param position an SFML vector representing the position
   * @param size an SFML vector representing the size
   */
  Key(sf::Vector2f const&, sf::Vector2f const&);
  Key(sf::Vector2f const&, sf::Vector2f const&, int const&);

  /**
   * Used to check if the Character intersects with the Key,
   * allowing it to mark the Key as "taken".
   * @param character the Character used to check the intersection
   */
  void checkTaken(Character const&);

  /**
   * Retrieve the current "taken" state.
   *
   * @return true if the character has already collected the key, false
   * otherwise
   */
  bool getTaken() const;

  void loadTexture();
};
}  // namespace fnad

#endif