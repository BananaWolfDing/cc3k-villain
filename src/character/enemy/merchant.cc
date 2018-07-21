#include "merchant.h"
#include <cstdlib>
#include <ctime>
merchant::merchant(): enemy{30, 70, 5, "Merchant", 'M'} {}

int merchant::attack(cell &defender) {
  if (!isNeutral()) {
    srand(time(NULL));
    if (rand() % 2)
      return defender.defend(*this);
  }

  return 0;
}

bool merchant::isNeutral() const {
  return neutral;
}

void merchant::die(player &) {}
