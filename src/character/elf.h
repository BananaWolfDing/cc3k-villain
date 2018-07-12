#ifndef ELF_H
#define ELF_H

#include "enemy.h"
#include "../treasure"

class elf : public enemy {
public:
  elf();
  void attack(character &defender);
};

#endif
