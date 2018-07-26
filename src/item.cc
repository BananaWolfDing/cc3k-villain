#include "item.h"

item::item(std::string name, char display, enemy *guardian):
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

void item::setGuardian(enemy *guardian) {
  this->guardian = guardian;
}

enemy *item::getGuardian() const {
  return guardian;
}