#ifndef ELF_H
#define ELF_H

#include "enemy.h"

class elf : public enemy {
public:
  elf();
  std::string attack(cell &defender);
};

#endif
