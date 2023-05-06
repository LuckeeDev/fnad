#include <vector>

#ifndef EPIDEMIC_HPP
#define EPIDEMIC_HPP

namespace fnad {
class Enemy;

class Epidemic {
 private:
  std::vector<Enemy> enemies_;

 public:
  void evolve();
};
}  // namespace fnad

#endif