#include "restoreHealth.h"
#include "../../character.h"

restoreHealth::restoreHealth(): potion{"restoreHealth"} {}

void restoreHealth::use() {
  if (PC->getRace() != "drow")
    PC->addHp(10);
  else
    PC->addHp(15);
}
