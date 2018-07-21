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
  cell *guard;
public:
  character(int hp, int hpMax, int atk, int def, std::string race, char display);

  int getHp() const;
  int getAtk() const;
  int getDef() const;
  std::string getRace() const;
  cell *getGuard() const;

  virtual void addHp(int inc);
  void addAtk(int inc);
  void addDef(int inc);
  void setGuard(item *treasure);

  virtual void die(player &killer);
  virtual int attack(cell &defender);
  virtual int defend(cell &attacker);
};

#endif
