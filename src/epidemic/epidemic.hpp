#ifndef EPIDEMIC_HPP
#define EPIDEMIC_HPP

#include <SFML/Graphics.hpp>
#include <vector>

#include "../entities/enemy/enemy.hpp"

namespace fnad {
struct SIRState {
  double s{1.};
  double i{1.};
  double r{0.};

  SIRState() = default;
  SIRState(int, int, int);
};

struct SIRParams {
  double beta{0.7};
  double gamma{0.05};

  SIRParams() = default;
  SIRParams(double, double);
};

class Epidemic final : public sf::Drawable {
 private:
  SIRState sir_state_;
  SIRParams sir_params_;

  std::vector<Enemy> enemies_;

  // Rate of how many days (in the model) pass each second (in-game)
  double const DAYS_PER_SECOND_{0.5};

  virtual void draw(sf::RenderTarget&, sf::RenderStates) const;

 public:
  /**
   * Create an epidemic with default SIRState and SIRParams values.
   * You can set the initial state and the initial params through
   * `resetSIRState` and `setSIRParams`.
   */
  Epidemic() = default;

  /**
   * @return a reference to the vector containing all enemies in the game
   */
  std::vector<Enemy> const& getEnemies() const;

  /**
   * Set the SIR state. This removes every enemy in the epidemic and then
   * creates a new vector of enemies.
   *
   * @param state the new SIR state
   * @param map the map to spawn the enemies in
   */
  void resetSIRState(SIRState const&, Map&);

  /**
   * Set the SIR params.
   *
   * @param params the new SIR params
   */
  void setSIRParams(SIRParams const&);

  /**
   * @return the current SIR state.
   */
  SIRState getSIRState() const;

  /**
   * Counts how many enemies have the specified `status`.
   *
   * @param status the status to check for
   * @return number of `status` enemies
   */
  int count(Status const&) const;

  /**
   * Evolve the pandemic for a specified time and then move all enemies, either
   * towards the character (if they're infected and they can see the character)
   * or randomly (in every other situation).
   *
   * @param dt how long should the pandemic evolve for
   * @param character the character the enemies should point towards
   */
  void evolve(sf::Time const&, Character const&);
};
}  // namespace fnad

#endif