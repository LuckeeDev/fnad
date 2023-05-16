#include "game.hpp"

namespace fnad {
Game::Game(sf::RenderWindow* window, sf::View* view, Character* character,
           Epidemic* epidemic, Map* map)
    : window_{window},
      view_{view},
      character_{character},
      epidemic_{epidemic},
      map_{map} {}

Game::~Game() {
  delete window_;
  delete view_;
  delete character_;
  delete epidemic_;
  delete map_;
}

Game Game::create() {
  sf::RenderWindow* window =
      new sf::RenderWindow(sf::VideoMode(960, 640), "Map test");
  window->setFramerateLimit(60);

  sf::View* view =
      new sf::View(sf::Vector2f(100.f, 100.f), sf::Vector2f(300.f, 200.f));

  Map* map = new Map("assets/map/test.tmx");
  auto const map_bounds = static_cast<sf::Vector2f>(map->getBounds());

  Epidemic* epidemic = new Epidemic(99, 1, map_bounds, view);

  Character* character = new Character();

  return Game(window, view, character, epidemic, map);
}

void Game::run() const {
  while (window_->isOpen()) {
    sf::Event event;
    while (window_->pollEvent(event)) {
      if (event.type == sf::Event::Closed) window_->close();
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
      view_->move(-5.f, 0.f);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
      view_->move(5.f, 0.f);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
      view_->move(0.f, -5.f);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
      view_->move(0.f, 5.f);
    }

    window_->clear(sf::Color::Black);

    window_->setView(*view_);

    window_->draw(*map_);

    window_->display();
  }
}
}  // namespace fnad