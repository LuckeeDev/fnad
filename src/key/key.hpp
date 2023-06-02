#ifndef KEY_HPP
#define KEY_HPP

#include <SFML/Graphics.hpp>

namespace fnad {
class Character;

class Key final : public sf::RectangleShape {
 private:
  static sf::Texture texture_;
  bool taken_{false};

 public:
  static void loadTexture();

  /**
   * Construct a Key object.
   *
   * @param position an SFML vector representing the position
   * @param size an SFML vector representing the size
   * @param key_index the index of key's texture
   */
  Key(sf::Vector2f const&, sf::Vector2f const&, int);

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
};
}  // namespace fnad

#endif