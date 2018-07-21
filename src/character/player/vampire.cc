#include "vampire.h"

vampire::vampire(): player{50, 25, 25, "vampire", '@'} {}

void vampire::addHp(int inc) {
  hp += inc;
}

int vampire::attack(character &defender) {
  int damage = defender.defend(*this);
  if (defender.getRace() == "dwarf")
    addHp(-5);
  else
    addHp(5);

  return damage;
}
