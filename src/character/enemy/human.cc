#include "human.h"

human::human(): enemy{140, 20, 20, "human", 'H'} {}

void human::die(character &killer) {
  // killer.addGold(4);
  // here we should add code to generate two piles of gold on map instead of directly giving them to player
}
