#include "woundAttack.h"

woundAttack::woundAttack(): potion{"woundAttack"} {}

void woundAttack::use() {
  if (PC->getRace() != "Drow")
    PC->addAtk(-5);
  else
    PC->addAtk(-7);
}
