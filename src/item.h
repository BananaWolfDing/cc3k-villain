#ifndef ITEM_H
#define ITEM_H

#include <string>

class character;

class item : public cell {
  std::string name;
  char display;
  character *guard;
public:
  item(std::string name, char display, character *guard = nullptr);

  char getDisplay() const;
  std::string getName() const;
  character *getGuard() const;

  virtual void use();
  virtual void unuse();
  void setGuard(character *guard);
};

#endif
