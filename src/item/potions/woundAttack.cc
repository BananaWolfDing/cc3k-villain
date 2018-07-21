#include "woundAttack.h"
#include "../../character.h"

woundAttack::woundAttack(): potion{"woundAttack"} {}

void woundAttack::use() {
  if (PC->getRace() != "drow")
    PC->addAtk(-5);
  else
    PC->addAtk(-7);
}
