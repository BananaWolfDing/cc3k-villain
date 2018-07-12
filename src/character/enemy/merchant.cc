#include "merchant.h"

merchant::merchant(): enemy{30, 70, 5, "Merchant", "M"}, isNeutral{true} {}

int merchant::attack(character &defender) {
  if (!isNeutral)
    if (rand() % 2)
      return defender.defend(*this);

  return 0;
}

bool merchant::isNeutral() const {
  return neutral;
}

void merchant::die(character) {}
