#ifndef POTION_H
#define POTION_H

#include <string>
#include "item.h"

class potion : public item {
public:
  potion(std::string name);
};

#endif
