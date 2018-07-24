#include <algorithm>
#include <cmath>
#include "character.h"
#include <iostream>
#include "character/enemy/merchant.h"
#include "character/enemy/enemy.h"

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

std::string character::attack(cell &defender) {
  int damage = defender.defend(*this);

  std::string action = getName() + " attacks " + defender.getName();
  if (damage)
    action += " and deals " + std::to_string(damage) + " damage";
  else
    action += " but missed";

  return action;
}

int character::defend(cell &attacker) {
  if(this->getName() == "Merchant"){
    enemy *e = dynamic_cast<enemy *>(this);
    merchant *m = dynamic_cast<merchant *>(e);
    m->becomeHostile();
    std::cout << "Merchant is neutral or not: "<< m->isNeutral() << std::endl;

  }
  int damage = std::min(getHp(), (int) ceil(100 * attacker.getAtk() / (100 + getDef())));
  addHp(-damage);
  return damage;
}
