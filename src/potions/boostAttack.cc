#include "boostAttack.h"
#include "../character.h"

boostAttack::boostAttack(): potion{"boostAttack"} {}

void boostAttack::use() {
  if (PC->getRace() != "drow")
    PC->addAtk(5);
  else
    PC->addAtk(7);
}

void boostAttack::unuse() {
  if (PC->getRace() != "drow")
    PC->addAtk(-5);
  else
    PC->addAtk(-7);
}
