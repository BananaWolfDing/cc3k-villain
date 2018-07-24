#include "halfling.h"
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <algorithm>

halfling::halfling(): enemy{100, 15, 20, "Halfling", 'L'} {}

int halfling::defend(cell &attacker) {
  if (rand() % 2) {
    int damage = std::min(getHp(), (int) ceil(100 * attacker.getAtk() / (100 + getDef())));
    addHp(-damage);
    return damage;
  }
  else
    return 0;
}
