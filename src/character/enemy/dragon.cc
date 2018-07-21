#include "dragon.h"

dragon::dragon(item *guard): enemy{150, 20, 20, "dragon", 'D'} {
  this->guard = guard;
  this->guard->setGuardian(this);
}

void dragon::die(character) {
  this->guard->setGuardian(nullptr);
  this->guard = nullptr;
}
