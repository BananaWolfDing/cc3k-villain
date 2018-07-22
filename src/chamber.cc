#include <ctime>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include "chamber.h"
#include "cell.h"
#include <iostream>
cell *chamber::randomCell() {
  int n = cells.size();
  if (n == 0)
    return nullptr;
  else {
    return cells[rand() % n];
  }
}

cell *chamber::randomEmptyCell() {
  cell *c = randomCell();
  while (!c->getEmpty() || (c->getRow() == PCBornRow && c->getCol() == PCBornCol))
    c = randomCell();

  return c;
}

cell *chamber::dragonCell(cell *treasure) {
  std::vector<cell *> nearby = treasure->getNeighbour();
  int n = nearby.size();

  if (n == 0)
    return nullptr;
  else {
    int m = rand() % n;
    while (!nearby[m]->getEmpty())
      m = rand() % n;
    return nearby[m];
  }
}

bool chamber::validDragonHoardCell(cell *c) {
  std::vector<cell *> nearby = c->getNeighbour();
  for (auto itr = nearby.begin(); itr != nearby.end(); itr++)
    if ((*itr)->getEmpty()) return true;

  return false;
}

cell *chamber::dragonHoardCell() {
  cell *c = randomEmptyCell();

  while (validDragonHoardCell(c))
    c = randomEmptyCell();

  return c;
}

void chamber::addCell(cell *c) {
  cells.push_back(c);
}

bool chamber::playerRoom() const {
  return playerHere;
}

cell *chamber::createStair() {
  cell *c = randomEmptyCell();
  c->setStair();
  return c;
}

inline void replace(cell *origCell, cell *newCell) {
  newCell->setRow(origCell->getRow());
  newCell->setCol(origCell->getCol());
  newCell->setPC(origCell->getPC());
  std::vector<cell *> neighbours = origCell->getNeighbour();
  newCell->setNeighbour(neighbours);
  for (auto itr = neighbours.begin(); itr != neighbours.end(); itr++) {
    (*itr)->removeNeighbour(origCell);
    (*itr)->addNeighbour(newCell);
  }
}

cell *chamber::createHuman() {
  cell *c = randomEmptyCell();
  human *npc = new human;
  replace(c, npc);
  delete c;
  return npc;
}

cell *chamber::createDwarf() {
  cell *c = randomEmptyCell();
  dwarf *npc = new dwarf;
  replace(c, npc);
  delete c;
  return npc;
}

cell *chamber::createHalfling() {
  cell *c = randomEmptyCell();
  halfling *npc = new halfling;
  replace(c, npc);
  delete c;
  return npc;
}

cell *chamber::createElf() {
  cell *c = randomEmptyCell();
  elf *npc = new elf;
  replace(c, npc);
  delete c;
  return npc;
}

cell *chamber::createOrc() {
  cell *c = randomEmptyCell();
  orc *npc = new orc;
  replace(c, npc);
  delete c;
  return npc;
}

cell *chamber::createMerchant() {
  cell *c = randomEmptyCell();
  merchant *npc = new merchant;
  replace(c, npc);
  delete c;
  return npc;
}

cell *chamber::createDragon(cell *treasure) {
  cell *c = dragonCell(treasure);
  dragon *npc = new dragon(treasure);
  replace(c, npc);
  delete c;
  return npc;
}

void chamber::setPC(player *PC) {
  cell *c = randomEmptyCell();
  PCBornRow = c->getRow();
  PCBornCol = c->getCol();
  PC->setRow(c->getRow());
  PC->setCol(c->getCol());
  PC->setNeighbour(c->getNeighbour());
  playerHere = true;
}

cell *chamber::createBA() {
  cell *c = randomEmptyCell();
  boostAttack *pot = new boostAttack;
  replace(c, pot);
  delete c;
  return pot;
}

cell *chamber::createBD() {
  cell *c = randomEmptyCell();
  boostDefence *pot = new boostDefence;
  replace(c, pot);
  delete c;
  return pot;
}

cell *chamber::createPH() {
  cell *c = randomEmptyCell();
  poisonHealth *pot = new poisonHealth;
  replace(c, pot);
  delete c;
  return pot;
}

cell *chamber::createRH() {
  cell *c = randomEmptyCell();
  restoreHealth *pot = new restoreHealth;
  replace(c, pot);
  delete c;
  return pot;
}

cell *chamber::createWA() {
  cell *c = randomEmptyCell();
  woundAttack *pot = new woundAttack;
  replace(c, pot);
  delete c;
  return pot;
}

cell *chamber::createWD() {
  cell *c = randomEmptyCell();
  woundDefence *pot = new woundDefence;
  replace(c, pot);
  delete c;
  return pot;
}

cell *chamber::createGold(int amount) {
  cell *c;
  if (amount != 6)
    c = randomEmptyCell();
  else
    c = dragonHoardCell();

  gold *g = new gold(amount);
  replace(c, g);
  delete c;
  return g;
}
