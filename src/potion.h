#ifndef POTION_H
#define POTION_H

#include <string>
#include "item.h"

class potion : public item {
public:
  Potion(std::string name);
  void use() override;
};

#endif
