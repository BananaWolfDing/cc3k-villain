#include "cell.h"

cell::cell(int row, int col, char display = '.'):
  row{row}, col{col}, display{display}, stair{false}, empty{true} {}

void setPC(player *PC) {
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

bool cell::getStair() {
  return stair;
}

int cell::getRow() {
  return row;
}

int cell::getCol() {
  return col;
}

std::vector<cell *> cell::getNeighbour() const {
  return neighbour;
}
