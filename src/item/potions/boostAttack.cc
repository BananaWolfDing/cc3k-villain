#include "boostAttack.h"
#include "../../character/allCharacters.h"

boostAttack::boostAttack(): potion{"boostAttack"} {}

void boostAttack::use() {
  if (PC->getRace() != "drow")
    PC->addAtk(5);
  else
    PC->addAtk(7);
}
