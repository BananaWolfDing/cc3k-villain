#ifndef ELF_H
#define ELF_H

#include "enemy.h"
#include "../treasure"

class elf : public enemy {
public:
  elf();
  int attack(character &defender);
};

#endif
