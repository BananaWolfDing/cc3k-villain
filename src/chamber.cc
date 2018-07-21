#include <ctime>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include "chamber.h"
#include "cell.h"

cell *chamber::randomCell() {
  int n = cells.size();
  if (n == 0)
    return nullptr;
  else {
    srand(time(NULL));
    return cells[rand() % n];
  }
}

cell *chamber::randomEmptyCell() {
  cell *c = randomCell();
  while (!c->getEmpty() && (c->getRow() != PCBornRow) || c->getCol() != PCBornCol)
    c = randomCell();

  return c;
}

cell *chamber::dragonCell(cell *treasure) {
  std::vector<cell *> nearby = treasure->getNeighbour();
  srand(time(NULL));
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

cell *chamber::createHuman() {
  cell *c = randomEmptyCell();
  human *npc = new human;
  npc->setNeighbour(c->getNeighbour());
  npc->setRow(c->getRow());
  npc->setCol(c->getCol());
  delete c;
  return npc;
}

cell *chamber::createDwarf() {
  cell *c = randomEmptyCell();
  dwarf *npc = new dwarf;
  npc->setNeighbour(c->getNeighbour());
  npc->setRow(c->getRow());
  npc->setCol(c->getCol());
  delete c;
  return npc;
}

cell *chamber::createHalfling() {
  cell *c = randomEmptyCell();
  halfling *npc = new halfling;
  npc->setNeighbour(c->getNeighbour());
  npc->setRow(c->getRow());
  npc->setCol(c->getCol());
  delete c;
  return npc;
}

cell *chamber::createElf() {
  cell *c = randomEmptyCell();
  elf *npc = new elf;
  npc->setNeighbour(c->getNeighbour());
  npc->setRow(c->getRow());
  npc->setCol(c->getCol());
  delete c;
  return npc;
}

cell *chamber::createOrc() {
  cell *c = randomEmptyCell();
  orc *npc = new orc;
  npc->setNeighbour(c->getNeighbour());
  npc->setRow(c->getRow());
  npc->setCol(c->getCol());
  delete c;
  return npc;
}

cell *chamber::createMerchant() {
  cell *c = randomEmptyCell();
  merchant *npc = new merchant;
  npc->setNeighbour(c->getNeighbour());
  npc->setRow(c->getRow());
  npc->setCol(c->getCol());
  delete c;
  return npc;
}

cell *chamber::createDragon(cell *treasure) {
  cell *c = dragonCell(treasure);
  dragon *npc = new dragon(treasure);
  npc->setNeighbour(c->getNeighbour());
  npc->setRow(c->getRow());
  npc->setCol(c->getCol());
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
  pot->setNeighbour(c->getNeighbour());
  pot->setRow(c->getRow());
  pot->setCol(c->getCol());
  delete c;
  return pot;
}

cell *chamber::createBD() {
  cell *c = randomEmptyCell();
  boostDefence *pot = new boostDefence;
  pot->setNeighbour(c->getNeighbour());
  pot->setRow(c->getRow());
  pot->setCol(c->getCol());
  delete c;
  return pot;
}

cell *chamber::createPH() {
  cell *c = randomEmptyCell();
  poisonHealth *pot = new poisonHealth;
  pot->setNeighbour(c->getNeighbour());
  pot->setRow(c->getRow());
  pot->setCol(c->getCol());
  delete c;
  return pot;
}

cell *chamber::createRH() {
  cell *c = randomEmptyCell();
  restoreHealth *pot = new restoreHealth;
  pot->setNeighbour(c->getNeighbour());
  pot->setRow(c->getRow());
  pot->setCol(c->getCol());
  delete c;
  return pot;
}

cell *chamber::createWA() {
  cell *c = randomEmptyCell();
  woundAttack *pot = new woundAttack;
  pot->setNeighbour(c->getNeighbour());
  pot->setRow(c->getRow());
  pot->setCol(c->getCol());
  delete c;
  return pot;
}

cell *chamber::createWD() {
  cell *c = randomEmptyCell();
  woundDefence *pot = new woundDefence;
  pot->setNeighbour(c->getNeighbour());
  pot->setRow(c->getRow());
  pot->setCol(c->getCol());
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
  g->setNeighbour(c->getNeighbour());
  g->setRow(c->getRow());
  g->setCol(c->getCol());
  delete c;
  return g;
}
