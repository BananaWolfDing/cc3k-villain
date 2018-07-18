#ifndef POISON_HEALTH_H
#define POISON_HEALTH_H

#include "../../potion.h"

class poisonHealth : public potion {
public:
  poisonHealth();
  void use() override;
};

#endif
