#ifndef ENEMY_H
#define ENEMY_H

#include "../player/player.h"

class enemy : public character {
public:
  enemy(int maxHp, int atk, int def, std::string race, char display);
  std::string attack(cell& defender);
  virtual void die(player &killer);
};

#endif
