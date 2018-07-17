#ifndef GOBLIN_H
#define GOBLIN_H

#include "player.h"

class goblin : public player {
public:
  goblin();
  int defend(character &attacker) override;
};

#endif
