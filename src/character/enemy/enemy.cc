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

std::string enemy::attack(cell &defender) {
  int damage = 0;
  if (rand() % 2)
    damage = defender.defend(*this);

  std::string action = getName() + " attacks " + defender.getName();
  if (damage)
    action += " and deals " + std::to_string(damage) + " damage";
  else
    action += " but missed";

  return action;
}
