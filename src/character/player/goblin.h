#ifndef GOBLIN_H
#define GOBLIN_H

#include "player.h"

class goblin : public player {
public:
  goblin();
  int defend(cell &attacker) override;
};

#endif
