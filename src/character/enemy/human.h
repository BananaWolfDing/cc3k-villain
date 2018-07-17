#ifndef HUMAN_H
#define HUMAN_H

#include "enemy.h"

class human : public enemy {
  void die(character &killer) override;
public:
  human();
};

#endif
