#include "woundDefence.h"

woundDefence::woundDefence(): potion{"woundDefence"} {}

void woundDefence::use() {
  if (PC->getRace() != "Drow")
    PC->addDef(-5);
  else
    PC->addDef(-7);
}
