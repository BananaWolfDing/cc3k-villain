#include "elf.h"
#include <ctime>
#include <cstdlib>

elf::elf(): enemy{140, 30, 10, "Elf", 'E'} {}

int elf::attack(character &defender) {
  int damage = 0;

  if (rand() % 2)
    damage += defender.defend(*this);

  if (defender.getRace() != "drow" && rand() % 2)
    damage += defender.defend(*this);

  return damage;
}
