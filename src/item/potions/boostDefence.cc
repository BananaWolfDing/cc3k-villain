#include "boostDefence.h"

boostDefence::boostDefence(): potion{"boostDefence"} {}

void boostDefence::use() {
  if (PC->getRace() != "drow")
    PC->addDef(5);
  else
    PC->addDef(7);
}
