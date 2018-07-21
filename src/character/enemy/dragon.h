#ifndef DRAGON_H
#define DRAGON_H

#include "enemy.h"
#include "../../item/gold.h"

class dragon : public enemy {
public:
  dragon(cell *guard);
  void die(player &killer) override;
};

#endif
