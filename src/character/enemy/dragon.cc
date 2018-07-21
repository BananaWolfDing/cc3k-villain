#include "dragon.h"

dragon::dragon(cell *guard): enemy{150, 20, 20, "dragon", 'D'} {
  this->guard = guard;
  this->guard->setGuardian(this);
}

void dragon::die(player &) {
  this->guard->setGuardian(nullptr);
  this->guard = nullptr;
}
