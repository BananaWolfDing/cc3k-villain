#include "goblin.h"

goblin::goblin(): character{110, 15, 20, "drow", "@"} {}

int goblin::defend(character &attacker) {
  int damage = 0;
  if (attacker.getRace() == "orcs")
    damage = max(getHp(), 2 * cell(100 * attacker.getAtk() / (100 + getDef())));
  else
    damage = max(getHp(), cell(100 * attacker.getAtk() / (100 + getDef())));

  addHp(-damage);
  return damage;
}
