#include "woundDefence.h"
#include "../character.h"

woundDefence::woundDefence(): potion{"woundDefence"} {}

void woundDefence::use() {
  if (PC->getRace() != "drow")
    PC->addDef(-5);
  else
    PC->addDef(-7);
}
