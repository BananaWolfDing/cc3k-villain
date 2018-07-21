#ifndef HALFLING_H
#define HALFLING_H

#include "enemy.h"

class halfling : public enemy {
public:
  halfling();
  int defend(character &attacker) override;
};

#endif
