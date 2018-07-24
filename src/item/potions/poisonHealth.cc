#include "poisonHealth.h"

poisonHealth::poisonHealth(): potion{"poisonHealth"} {}

void poisonHealth::use() {
  if (PC->getRace() != "Drow")
    PC->addHp(-10);
  else
    PC->addHp(-15);
}
