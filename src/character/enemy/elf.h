#ifndef ELF_H
#define ELF_H

#include "enemy.h"

class elf : public enemy {
public:
  elf();
  int attack(character &defender);
};

#endif
