#ifndef CHARACTER_H
#define CHARACTER_H

#include <vector>
#include <string>
#include "potion.h"
#include "cell.h"
#include "character\allCharacters.h"

class character : public cell{
  std::string race;
protected:
  int hp, hpMax, atk, stdAtk, def, stdDef;
  item *guard;
public:
  character(int hp, int hpMax, int atk, int def, std::string race, char display);

  int getHp() const;
  int getAtk() const;
  int getDef() const;
  char getDisplay() const;
  std::string getRace() const;
  item *getGuard() const;

  virtual void addHp(int inc);
  void addAtk(int inc);
  void addDef(int inc);
  void setGuard(item *treasure);

  virtual int attack(character &defender);
  virtual int defend(character &attacker);
};

#endif
