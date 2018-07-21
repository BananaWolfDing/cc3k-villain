#include "item.h"

item::item(std::string name, char display, character *guardian = nullptr):
  name{name}, display{display}, guardian{guardian}, empty{false} {}

char item::getDisplay() const {
  return display;
}

std::string item::getName() const {
  return name;
}

void item::setGuardian(enemy *guardian) {
  this->guardian = guardian;
}

enemy *item::getGuardian() const{
  return guardian;
}