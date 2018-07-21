#ifndef WOUND_ATTACK_H
#define WOUND_ATTACK_H

#include "../../potion.h"

class woundAttack : public potion {
public:
  woundAttack();
  void use() override;
};

#endif
