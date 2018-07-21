#ifndef DRAGON_H
#define DRAGON_H

#include "enemy.h"
#include "../../item/gold.h"

class dragon : public enemy {
  void die(character &killer) override;
public:
  dragon(item *guard);
};

#endif
