#ifndef ITEM_H
#define ITEM_H

#include <string>
#include "cell.h"

class enemy;
class character;

class item : public cell {
protected:
  std::string name;
  cell *guardian;
public:
  item(std::string name, char display, cell *guardian = nullptr);

  char getDisplay() const;
  std::string getName() const;
  cell *getGuardian() const;
  void setGuardian(cell *guardian);
  virtual void use() = 0;
};

#endif
