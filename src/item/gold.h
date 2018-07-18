#ifndef GOLD_H
#define GOLD_H

#include <string>
#include "../character.h"

class gold : public item {
  int amount;
public:
  gold(int amount);
  void use() override;
};

#endif
