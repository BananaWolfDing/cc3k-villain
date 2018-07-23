#include "enemy.h"
#include "../player/player.h"
#include <cstdlib>
#include <ctime>
#include <iostream>

enemy::enemy(int maxHp, int atk, int def, std::string race, char display): 
	character{maxHp, atk, def, race, display} {}

void enemy::die(player &killer) {
  killer.addGold(1 + rand() % 2);
}

int enemy::attack(cell &defender) {
    int i = rand()%2;
    if(i == 0) {
        std::cout << "1:" << i << std::endl;
        return 0;
    }
    else {
        std::cout << "2:" << i << std::endl;
        return defender.defend(*this);
    }
}
