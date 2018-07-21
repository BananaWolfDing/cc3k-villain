#include "enemy.h"
#include "../player/player.h"
#include <cstdlib>
#include <ctime>
enemy::enemy(int maxHp, int atk, int def, std::string race, char display): 
	character{maxHp, atk, def, race, display} {}

void enemy::die(player &killer) {
  srand(time(NULL));
  killer.addGold(1 + rand() % 2);
}
