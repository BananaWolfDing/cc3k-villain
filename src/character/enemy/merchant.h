#ifndef MERCHANT_H
#define MERCHANT_H

#include "enemy.h"

class merchant : public enemy {
  bool neutral = true;
public:
  merchant();
  bool isNeutral() const;
  int attack(cell &defender) override;
  void die(player &PC) override;
  void becomeHostile();
};

#endif
