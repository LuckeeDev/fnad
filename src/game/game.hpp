#include "../map/map.hpp"

#ifndef GAME_HPP
#define GAME_HPP

namespace fnad {
class Game final {
 private:
  Map map_;

 public:
  void run() const;
};
}  // namespace fnad

#endif