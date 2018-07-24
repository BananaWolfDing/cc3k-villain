#include "boostDefence.h"

boostDefence::boostDefence(): potion{"boostDefence"} {}

void boostDefence::use() {
  if (PC->getRace() != "Drow")
    PC->addDef(5);
  else
    PC->addDef(7);
}
