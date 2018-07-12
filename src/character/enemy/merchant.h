#ifndef MERCHANT_H
#define MERCHANT_H

#include "enemy.h"
#include "../treasure"

class merchant : public enemy {
  static bool neutral;
public:
  dwarf();
  bool isNeutral() const;
  int attack(character &defender) override;
};

#endif
