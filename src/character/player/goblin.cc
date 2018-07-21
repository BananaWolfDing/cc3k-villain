#include "goblin.h"
#include <algorithm>

goblin::goblin(): player{110, 15, 20, "drow", '@'} {}

int goblin::defend(character &attacker) {
  int damage = 0;
  if (attacker.getRace() == "orc")
    damage = std::max(getHp(), 2 * cell(100 * attacker.getAtk() / (100 + getDef())));
  else
    damage = std::max(getHp(), cell(100 * attacker.getAtk() / (100 + getDef())));

  addHp(-damage);
  return damage;
}
