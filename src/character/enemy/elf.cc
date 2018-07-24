#include "elf.h"
#include <ctime>
#include <cstdlib>

elf::elf(): enemy{140, 30, 10, "Elf", 'E'} {}

std::string elf::attack(cell &defender) {
  int damage = 0;
  if (rand() % 2)
    damage = defender.defend(*this);

  std::string action = getName() + " attacks " + defender.getName();
  if (damage)
    action += " and deals " + std::to_string(damage) + " damage";
  else
    action += " but missed";

  if (defender.getHp()) {
    action += "!\n";
    if (rand() % 2)
      damage = defender.defend(*this);
    else
      damage = 0;

    action += getName() + " attacks " + defender.getName();
    if (damage)
      action += " and deals " + std::to_string(damage) + " damage";
    else
      action += " but missed";
  }

  return action;
}
