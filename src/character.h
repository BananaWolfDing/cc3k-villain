#ifndef CHARACTER_H
#define CHARACTER_H

#include <vector>
#include <string>
#include "potion.h"
#include "cell.h"


class character : public cell{
  std::string race;
protected:
  int hp, hpMax, atk, stdAtk, def, stdDef;
  cell *guard;
public:
  character(int hp, int atk, int def, std::string race, char display);

  int getHp() const;
  int getAtk() const;
  int getDef() const;
  std::string getRace() const;
  std::string getName() const;
  cell *getGuard() const;

  virtual void addHp(int inc);
  void addAtk(int inc);
  void addDef(int inc);
  void setGuard(item *treasure);

  virtual void die(player &killer) = 0;
  virtual std::string attack(cell &defender);
  virtual int defend(cell &attacker);
};

#endif
