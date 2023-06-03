#include "epidemic.hpp"

#include <algorithm>
#include <cassert>
#include <cmath>
#include <numeric>
#include <random>

#include "../entities/character/character.hpp"
#include "../entities/enemy/enemy.hpp"
#include "../map/map.hpp"

namespace fnad {
// SIR constructors

SIRState::SIRState(int new_s, int new_i, int new_r)
    : s{static_cast<double>(new_s)},
      i{static_cast<double>(new_i)},
      r{static_cast<double>(new_r)} {
  assert(new_s > 0);
  assert(new_i > 0);
  assert(new_r >= 0);
}

SIRParams::SIRParams(double new_beta, double new_gamma)
    : beta{new_beta}, gamma{new_gamma} {
  assert(new_beta >= 0. && new_beta <= 1.);
  assert(new_gamma >= 0. && new_gamma <= 1.);
}

// Private methods

void Epidemic::draw(sf::RenderTarget& target, sf::RenderStates) const {
  auto const& view = target.getView();
  auto const& view_size = view.getSize();
  auto const& view_center = view.getCenter();
  auto const& top_left = view_center - view_size / 2.f;

  sf::FloatRect const view_rect{top_left, view_size};

  for (auto const& e : enemies_) {
    if (e.getStatus() != Status::removed &&
        view_rect.intersects(e.getGlobalBounds())) {
      target.draw(e);
    }
  }
}

// Public methods

std::vector<Enemy> const& Epidemic::getEnemies() const { return enemies_; }

void Epidemic::setSIRParams(SIRParams const& params) { sir_params_ = params; }

void Epidemic::resetSIRState(SIRState const& state, Map& map) {
  sir_state_ = state;

  enemies_.clear();

  auto& spawners = map.getSpawners();
  double const total_area =
      std::accumulate(spawners.begin(), spawners.end(), 0.,
                      [](double sum, Spawner const& spawner) {
                        return sum + spawner.getArea();
                      });

  enemies_.reserve(static_cast<unsigned int>(sir_state_.s + sir_state_.i));

  std::vector<double> weights;

  // Fill weights with the ratio between the Spawner area and the total area

  std::transform(spawners.begin(), spawners.end(), std::back_inserter(weights),
                 [&total_area](Spawner const& spawner) {
                   return spawner.getArea() / total_area;
                 });

  std::random_device rd;
  std::default_random_engine eng{rd()};
  std::discrete_distribution<unsigned int> spawner_dist{weights.begin(),
                                                        weights.end()};

  for (int j{}; j < sir_state_.i; j++) {
    auto& spawner = spawners[spawner_dist(eng)];

    enemies_.push_back(
        {map, spawner.getSpawnPoint(), fnad::Status::infectious});
  }

  for (int j{}; j < sir_state_.s; j++) {
    auto& spawner = spawners[spawner_dist(eng)];

    enemies_.push_back(
        {map, spawner.getSpawnPoint(), fnad::Status::susceptible});
  }
}

SIRState Epidemic::getSIRState() const { return sir_state_; }

int Epidemic::count(Status const& status) const {
  auto const count = std::count_if(
      enemies_.begin(), enemies_.end(),
      [&status](Enemy const& e) { return e.getStatus() == status; });

  return static_cast<int>(count);
}

void Epidemic::evolve(sf::Time const& dt, Character const& character) {
  auto const seconds = static_cast<double>(dt.asSeconds());
  auto const days = seconds * DAYS_PER_SECOND_;

  auto const N = static_cast<double>(enemies_.size());

  auto const new_s =
      sir_state_.s * (1. - days * sir_params_.beta * sir_state_.i / N);
  auto const new_i =
      sir_state_.i *
      (1. + days * (sir_params_.beta * sir_state_.s / N - sir_params_.gamma));
  auto const new_r = sir_state_.r + days * sir_params_.gamma * sir_state_.i;

  auto const new_i_integer = static_cast<int>(std::round(new_i));
  auto const i_count = count(Status::infectious);

  auto const new_r_integer = static_cast<int>(std::round(new_r));
  auto const r_count = count(Status::removed);

  sir_state_.s = new_s;
  sir_state_.i = new_i;
  sir_state_.r = new_r;

  auto n_to_infect = new_i_integer - i_count;
  auto n_to_remove = new_r_integer - r_count;

  for (auto& enemy : enemies_) {
    if (enemy.getStatus() == Status::susceptible && n_to_infect > 0) {
      enemy.infect();

      n_to_infect--;
    } else if (enemy.getStatus() == Status::infectious && n_to_remove > 0) {
      enemy.remove();

      n_to_remove--;
    }

    enemy.evolve(dt, character);
  }
}
}  // namespace fnad
