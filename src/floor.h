#ifndef FLOOR_H
#define FLOOR_H

#include <vector>
#include <string>

class floor {
  int width, height;
  int floorNum;
  bool freeze;
public:
  void freezeEnemy(bool f);
  void drawGrid();
  void executePC(string command);
  void executeEnemy();
};

#endif
