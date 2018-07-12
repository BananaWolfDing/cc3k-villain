#include "elf.h"

elf::elf(): enemy{140, 30, 10, "elf", 'E'} {}

void elf::attack(character &defender) {
  if (rand() % 2)
    defender.defend(*this);

  if (defender.getRace() != "drow" && rand() % 2)
    defender.defend(*this);
}
