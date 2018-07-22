#ifndef VAMPIRE_H
#define VAMPIRE_H

#include "player.h"
class vampire : public player {
public:
  vampire();
  void addHp(int inc);
  int attack(cell &defender);
};

#endif
