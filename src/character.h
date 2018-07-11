#ifndef CHARACTER_H
#define CHARACTER_H

#include <vector>
#include <string>
#include "potion.h"

class character : public cell{
  int hp, hpMax, atk, stdAtk, def, stdDef;
  int gold;
  std::string race;
  char display;
  std::vector<potion *> p;
  item *guard;
public:
  Character(int hp, int hpMax, int atk, int def, std::string race, char display);

  int getRow() const;
  int getCol() const;
  int getHp() const;
  int getAtk() const;
  int getDef() const;
  int getGold() const;
  char getDisplay() const;
  std::string getRace() const;
  item *getGuard() const;

  void setRow(int x);
  void setCol(int y);
  void addHp(int inc);
  void addAtk(int inc);
  void addDef(int inc);
  void addGold(int inc);
  void setGuard(item *treasure);

  void usePotion(potion *pot);
  virtual void attack(character &defender);
  virtual void defend(character &attacker);
};

#endif
