#include "human.h"
#include "../player/player.h"
human::human(): enemy{140, 20, 20, "human", 'H'} {}

void human::die(player &killer) {
  killer.addGold(4);
}
