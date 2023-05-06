#ifndef GAME_HPP
#define GAME_HPP

#include "../map/map.hpp"

namespace fnad {
class Game final {
 private:
  Map map_;

 public:
  void run() const;
};
}  // namespace fnad

#endif