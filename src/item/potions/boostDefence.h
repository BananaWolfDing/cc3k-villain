#ifndef BOOST_DEFENCE_H
#define BOOST_DEFENCE_H

#include "../../potion.h"
#include "../../character/player/player.h"

class boostDefence : public potion {
public:
  boostDefence();
  void use() override;
};

#endif
