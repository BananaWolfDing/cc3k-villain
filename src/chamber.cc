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

  std::cout << "The random empty cell we return: (" << c->getRow() << ", " << c->getCol() << ")\n";
  return c;
}

void chamber::updateCell(cell *origCell, cell *newCell) {
  for (auto itr = cells.begin(); itr != cells.end(); itr++)
    if (*itr == origCell) {
      *itr = newCell;
      break;
    }
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

  while (!validDragonHoardCell(c))
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

cell *chamber::createHuman() {
  cell *c = randomEmptyCell();
  std::cout << "The random empty cell we got: (" << c->getRow() << ", " << c->getCol() << ")\n";
  cell *npc = new human;
  updateCell(c, npc);
  npc->replaceCell(c);
  return npc;
}

cell *chamber::createDwarf() {
  cell *c = randomEmptyCell();
  cell *npc = new dwarf;
  updateCell(c, npc);
  npc->replaceCell(c);
  return npc;
}

cell *chamber::createHalfling() {
  cell *c = randomEmptyCell();
  cell *npc = new halfling;
  npc->replaceCell(c);
  return npc;
}

cell *chamber::createElf() {
  cell *c = randomEmptyCell();
  cell *npc = new elf;
  updateCell(c, npc);
  npc->replaceCell(c);
  return npc;
}

cell *chamber::createOrc() {
  cell *c = randomEmptyCell();
  cell *npc = new orc;
  updateCell(c, npc);
  npc->replaceCell(c);
  return npc;
}

cell *chamber::createMerchant() {
  cell *c = randomEmptyCell();
  cell *npc = new merchant;
  updateCell(c, npc);
  npc->replaceCell(c);
  return npc;
}

cell *chamber::createDragon(cell *treasure) {
  cell *c = dragonCell(treasure);
  cell *npc = new dragon(treasure);
  updateCell(c, npc);
  npc->replaceCell(c);
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
  cell *pot = new boostAttack;
  updateCell(c, pot);
  pot->replaceCell(c);
  return pot;
}

cell *chamber::createBD() {
  cell *c = randomEmptyCell();
  cell *pot = new boostDefence;
  updateCell(c, pot);
  pot->replaceCell(c);
  return pot;
}

cell *chamber::createPH() {
  cell *c = randomEmptyCell();
  cell *pot = new poisonHealth;
  updateCell(c, pot);
  pot->replaceCell(c);
  return pot;
}

cell *chamber::createRH() {
  cell *c = randomEmptyCell();
  cell *pot = new restoreHealth;
  updateCell(c, pot);
  pot->replaceCell(c);
  return pot;
}

cell *chamber::createWA() {
  cell *c = randomEmptyCell();
  cell *pot = new woundAttack;
  updateCell(c, pot);
  pot->replaceCell(c);
  return pot;
}

cell *chamber::createWD() {
  cell *c = randomEmptyCell();
  cell *pot = new woundDefence;
  updateCell(c, pot);
  pot->replaceCell(c);
  return pot;
}

cell *chamber::createGold(int amount) {
  cell *c;
  if (amount != 6)
    c = randomEmptyCell();
  else
    c = dragonHoardCell();

  cell *g = new gold(amount);
  updateCell(c, g);
  g->replaceCell(c);
  return g;
}
