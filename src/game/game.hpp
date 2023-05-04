#include "../epidemic/epidemic.hpp"

#ifndef GAME_HPP
#define GAME_HPP

namespace fnad {
class Game : public Epidemic {
  void run() const;
};
}  // namespace fnad

#endif