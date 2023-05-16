#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include <string>
#include <unordered_map>

#include "src/map/map.hpp"

int main() {
  sf::RenderWindow window(sf::VideoMode(960, 640), "Map test");
  window.setFramerateLimit(60);
  sf::View view(sf::Vector2f(100.f, 100.f), sf::Vector2f(300.f, 200.f));

  window.setView(view);
  fnad::Map map("assets/map/test.tmx");

  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) window.close();
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
      view.move(-5.f, 0.f);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
      view.move(5.f, 0.f);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
      view.move(0.f, -5.f);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
      view.move(0.f, 5.f);
    }

    window.clear(sf::Color::Black);

    window.setView(view);

    window.draw(map);

    window.display();
  }
}