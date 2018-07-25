#include "cell.h"
#include <iostream>

cell::cell(int row, int col, char display):
  row{row}, col{col}, display{display}, stair{false}, empty{true} {}

cell::cell() {}

cell::~cell() {}

void cell::setPC(player *PC) {
  this->PC = PC;
}

void cell::setStair() {
  stair = true;
  empty = false;
  display = '\\';
}

void cell::setRow(int r) {
  row = r;
}

void cell::setCol(int c) {
  col = c;
}

void cell::setNeighbour(std::vector<cell *> n) {
  neighbour = n;
}

void cell::addNeighbour(cell *c) {
  neighbour.push_back(c);
}

void cell::removeNeighbour(cell *c) {
  for (auto itr = neighbour.begin(); itr != neighbour.end(); itr++)
    if (*itr == c) {
      neighbour.erase(itr);
      break;
    }
}

void cell::replaceCell(cell *c) {
  setRow(c->getRow());
  setCol(c->getCol());
  setPC(c->getPC());
  std::vector<cell *> theNeighbours = c->getNeighbour();
  setNeighbour(theNeighbours);
  for (auto itr = theNeighbours.begin(); itr != theNeighbours.end(); itr++) {
    (*itr)->removeNeighbour(c);
    (*itr)->addNeighbour(this);
  }

  delete c;
}

player *cell::getPC() const {
  return PC;
}

bool cell::isCharacter() const {
  return isCha;
}

char cell::getDisplay() const {
  return display;
}

bool cell::getEmpty() const {
  return empty;
}

bool cell::getStair() const {
  return stair;
}

int cell::getRow() const {
  return row;
}

int cell::getCol() const {
  return col;
}

std::vector<cell *> cell::getNeighbour() const {
  return neighbour;
}
