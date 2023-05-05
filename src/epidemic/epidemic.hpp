#include <vector>

#include "../entities/enemy/enemy.hpp"

#ifndef EPIDEMIC_HPP
#define EPIDEMIC_HPP

namespace fnad {
class Epidemic {
 private:
  std::vector<fnad::Enemy> enemies_;

 public:
  void evolve();
};
}  // namespace fnad

#endif