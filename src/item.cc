#include "item.h"

item::item(std::string name, char display, cell *guardian):
  name{name}, guardian{guardian} {
  this->display = display;
  this->empty = false;
}

std::string item::getName() const {
  return name;
}

char item::getDisplay() const {
  return display;
}

void item::setGuardian(cell *guardian) {
  this->guardian = guardian;
}

cell *item::getGuardian() const {
  return guardian;
}