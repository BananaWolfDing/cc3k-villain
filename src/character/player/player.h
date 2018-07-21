#ifndef PLAYER_H
#define PLAYER_H

#include "../../character.h"
#include <string>

class player : public character {
  int gold = 0;
public:
  player(int hpMax, int atk, int def, std::string race, char display);
  int getGold() const;
  void setGold(int gold);
  void addGold(int gold);
};

#endif
