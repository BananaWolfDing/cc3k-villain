#include "human.h"

human::human(): enemy{140, 20, 20, "human", 'H'} {}

void human::die(character &killer) {
  killer.addGold(4);
}
