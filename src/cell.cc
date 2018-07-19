#include "cell.h"

cell::cell(int row, int col, char display):
  row{row}, col{col}, display{display}, stair{false} {}

void cell::setStair() {
  stair = true;
}

bool cell::getStair() {
  return stair;
}
