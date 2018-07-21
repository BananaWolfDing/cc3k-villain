#include "player.h"

player::player(int hp, int atk, int def, std::string race, char display):
	character(hp, atk, def, race, display) 
{}

int player::getGold() const {
  return gold;
}

void player::setGold(int gold) {
  this->gold = gold;
}

void player::addGold(int gold) {
  this->gold += gold;
}
