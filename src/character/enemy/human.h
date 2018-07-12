#ifndef HUMAN_H
#define HUMAN_H

#include "enemy.h"
#include "../treasure"

class human : public enemy {
  void die(character &killer);
public:
  human();
};

#endif
