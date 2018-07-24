#include "vampire.h"
#include <cstdlib>
vampire::vampire(): player{50, 25, 25, "Vampire", '@'} {}

void vampire::addHp(int inc) {
  hp += inc;
}

std::string vampire::attack(cell &defender) {
  int damage = 0;
  if (rand() % 2)
    damage = defender.defend(*this);

  std::string action = getName() + " attacks " + defender.getName();
  if (damage) {
    action += " and deals " + std::to_string(damage) + " damage";
    if (defender.getRace() == "Dwarf")
      addHp(-5);
    else
      addHp(5);
  }
  else
    action += " but missed";

  return action;
}
