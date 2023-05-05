#include "../map/map.hpp"

#ifndef GAME_HPP
#define GAME_HPP

namespace fnad {
class Game final : public Map {
 public:
  void run() const;
};
}  // namespace fnad

#endif