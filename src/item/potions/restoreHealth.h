#ifndef RESTORE_HEALTH_H
#define RESTORE_HEALTH_H

#include "../../potion.h"

class restoreHealth : public potion {
public:
  restoreHealth();
  void use() override;
};

#endif
