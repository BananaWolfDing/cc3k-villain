#ifndef MERCHANT_H
#define MERCHANT_H

#include "enemy.h"

class merchant : public enemy {
  static bool neutral;
  void die(character &killer) override;
public:
  merchant();
  bool isNeutral() const;
  int attack(character &defender) override;
};

#endif
