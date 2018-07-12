#ifndef DRAGON_H
#define DRAGON_H

#include "enemy.h"
#include "../../treasure"

class dragon : public enemy {
  void die(character &killer) override;
public:
  dragon(cell *guard);
};

#endif
