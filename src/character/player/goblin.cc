#include "goblin.h"
#include <algorithm>
#include <cmath>

goblin::goblin(): player{110, 15, 20, "Drow", '@'} {}

int goblin::defend(cell &attacker) {
  int damage = 0;
  if (attacker.getRace() == "Orc")
    damage = std::min(getHp(), 1 * (int) ceil(150 * attacker.getAtk() / (150 + getDef())));
  else
    damage = std::min(getHp(), (int) ceil(100 * attacker.getAtk() / (100 + getDef())));

  addHp(-damage);
  return damage;
}
