#ifndef HALFLING_H
#define HALFLING_H

#include "enemy.h"
#include "../treasure"

class halfling : public enemy {
public:
  halfling();
  int defend(character &attacker) override;
};

#endif
