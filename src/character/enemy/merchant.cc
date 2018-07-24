#include "merchant.h"
#include <cstdlib>
#include <ctime>

merchant::merchant(): enemy{30, 70, 5, "Merchant", 'M'} {}

std::string merchant::attack(cell &defender) {
  if (!isNeutral()) {
    int damage = 0;
    if (rand() % 2)
      damage = defender.defend(*this);

    std::string action = getName() + " attacks " + defender.getName();
    if (damage)
      action += " and deals " + std::to_string(damage) + " damage";
    else
      action += " but missed";

    return action;
  }
  else
    return "";
}

bool merchant::isNeutral() const {
  return neutral;
}

void merchant::becomeHostile() {
  neutral = false;
}

void merchant::die(player &PC) {}
