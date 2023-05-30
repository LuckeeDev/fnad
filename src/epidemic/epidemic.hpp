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
struct SIRState {
  double s;
  double i;
  double r;
};

struct SIRParams {
  double beta{0.7};
  double gamma{0.05};
};

class Epidemic : public sf::Drawable {
 private:
  SIRState sir_state_;
  SIRParams sir_params_;

  std::vector<Enemy> enemies_;

  // Rate of how many days pass each second
  double const days_per_second_{0.5};

  virtual void draw(sf::RenderTarget&, sf::RenderStates) const;

 public:
  Epidemic(const int, const int, Map&);

  std::vector<Enemy> const& getEnemies() const;
  SIRState getSIRState() const;
  int count(Status const&) const;

  void evolve(const sf::Time&, Character const&);
};
}  // namespace fnad

#endif