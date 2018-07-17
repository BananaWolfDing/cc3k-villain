#ifndef BOOST_ATTACK_H
#define BOOST_ATTACK_H

#include "../potion.h"

class boostAttack : public potion {
public:
  boostAttack();
  void use() override;
};

#endif
