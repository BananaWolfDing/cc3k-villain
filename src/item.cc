#include "item.h"

item::item(std::string name, char display, character *guardian = nullptr):
  name{name}, display{display}, guardian{guardian}, empty{false} {}

void item::getDisplay() const {
  return display;
}

std::string item::getName() const {
  return name;
}

void item::setGuardian(character *guardian) {
  this->guardian = guardian;
}
