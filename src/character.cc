#include <algorithm> // Can we use this for max()?
#include <cmath>
#include "character.h"
#include <iostream>
character::character(int hp, int atk, int def, std::string race, char display):
  hp{hp}, hpMax{hp}, atk{atk}, stdAtk{atk}, def{def}, stdDef{def},
  race{race} {
    this->display = display;
    this->empty = false;
    this->isCha = true;
}

int character::getHp() const {
  return hp;
}

int character::getAtk() const {
  return atk;
}

int character::getDef() const {
  return def;
}

std::string character::getRace() const {
  return race;
}

std::string character::getName() const {
  return race;
}

cell *character::getGuard() const {
  return guard;
}

void character::addHp(int inc) {
  hp += inc;
  hp = std::min(hpMax, hp);
  hp = std::max(0, hp);
}

void character::addAtk(int inc) {
  atk += inc;
  atk = std::max(0, atk);
}

void character::addDef(int inc) {
  def += inc;
  def = std::max(0, def);
}

void character::setGuard(item *treasure) {
  guard = treasure;
}

int character::attack(cell &defender) {
  return defender.defend(*this);
}

int character::defend(cell &attacker) {
  int damage = std::min(getHp(), (int) ceil(100 * attacker.getAtk() / (100 + getDef())));
  addHp(-damage);
  return damage;
}
