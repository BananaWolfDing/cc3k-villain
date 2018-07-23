#include "goblin.h"
#include <algorithm>
#include <cmath>

goblin::goblin(): player{110, 15, 20, "drow", '@'} {}

int goblin::defend(cell &attacker) {
  int damage = 0;
  if (attacker.getRace() == "orc")
    damage = std::min(getHp(), 2 * (int) ceil(100 * attacker.getAtk() / (100 + getDef())));
  else
    damage = std::min(getHp(), (int) ceil(100 * attacker.getAtk() / (100 + getDef())));

  addHp(-damage);
  return damage;
}
