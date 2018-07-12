#include "dragon.h"

dragon::dragon(cell *guard): enemy{150, 20, 20, "dragon", 'D'} {
  this->guard = guard;
}

void dragon::die(character) {
  this->guard->guard = nullptr;
  this->guard = nullptr;
}
