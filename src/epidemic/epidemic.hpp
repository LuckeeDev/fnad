#ifndef EPIDEMIC_HPP
#define EPIDEMIC_HPP

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/View.hpp>
#include <SFML/System/Time.hpp>
#include <vector>

#include "../entities/enemy/enemy.hpp"

namespace fnad {
struct SIR {
  double s_;
  double i_;
  double r_;
};

class Epidemic : private SIR, public sf::Drawable {
 private:
  std::vector<Enemy> enemies_;

  double const beta_{0.7};
  double const gamma_{0.05};

  // Rate of how many days pass each second
  double const days_per_second_{0.5};

  sf::View& view_;

  virtual void draw(sf::RenderTarget&, sf::RenderStates) const;

 public:
  Epidemic(const int, const int, Map const&, sf::View&);

  std::vector<Enemy> const& getEnemies() const;
  SIR getSIRState() const;
  int count(Status const&) const;

  void evolve(const sf::Time&, Character const&);
};
}  // namespace fnad

#endif