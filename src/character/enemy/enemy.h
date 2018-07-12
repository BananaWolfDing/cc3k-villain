#ifndef ENEMY_H
#define ENEMY_H

#include "character.h"

class enemy : public character {
  virtual void die(character &dead);
public:
  enemy(int maxHp, int atk, int def, std::string race, char display);
};

#endif
