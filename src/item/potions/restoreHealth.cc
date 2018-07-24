#include "restoreHealth.h"

restoreHealth::restoreHealth(): potion{"restoreHealth"} {}

void restoreHealth::use() {
  if (PC->getRace() != "Drow")
    PC->addHp(10);
  else
    PC->addHp(15);
}
