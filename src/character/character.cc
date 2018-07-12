#include <algorithm> // Can we use this for max()?
#include <cmath>
#include "character.h"

character::character(int hp, int hpMax, int atk, int def, std::string race, char display):
  hp{hp}, hpMax{hp}, atk{atk}, stdAtk{atk}, def{def}, stdDef{def}, race{race}, display{display} {}

int character::getHp() const {
  return hp;
}

int character::getAtk() const {
  return atk;
}

int character::getDef() const {
  return def;
}

char character::getDisplay() const {
  return display;
}

std::string character::getRace() const {
  return race;
}

item *character::getGuard() const {
  return guard;
}

void character::addHp(int inc) {
  hp += inc;
}

void character::addAtk(int inc) {
  atk += inc;
}

void character::addDef(int inc) {
  def += inc;
}

void character::setGuard(item *treasure) {
  guard = treasure;
}

int character::attack(character &defender) {
  return defender.defend(*this);
}

int character::defend(character &attacker) {
  int damage = max(getHp(), cell(100 * attacker.getAtk() / (100 + getDef())));
  addHp(-damage);
  return damage;
}
