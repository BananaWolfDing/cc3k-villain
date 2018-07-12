#include "halfling.h"

halfling::halfling(): enemy{100, 15, 20, "halfling", 'L'} {}

void halfling::defend(character &attacker) {
  if (rand() % 2) {
    // here we should add code for common defend
  }
  else
    return 0;
}
