#include "halfling.h"

halfling::halfling(): enemy{100, 15, 20, "halfling", 'L'} {}

void halfling::defend(character &attacker) {
  if (rand() % 2) {
    int damage = max(getHp(), cell(100 * attacker.getAtk() / (100 + getDef())));
    addHp(-damage);
    return damage;
  }
  else
    return 0;
}
