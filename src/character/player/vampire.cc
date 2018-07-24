#include "vampire.h"

vampire::vampire(): player{50, 25, 25, "Vampire", '@'} {}

void vampire::addHp(int inc) {
  hp += inc;
}

int vampire::attack(cell &defender) {
  int damage = defender.defend(*this);
  if (defender.getRace() == "dwarf")
    addHp(-5);
  else
    addHp(5);

  return damage;
}
