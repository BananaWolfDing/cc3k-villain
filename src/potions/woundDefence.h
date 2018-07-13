#ifndef WOUND_DEFENCE_H
#define WOUND_DEFENCE_H

#include "../potion.h"

class woundDefence : public potion {
public:
  woundDefence();
  void use() override;
};

#endif
