#ifndef CELL_H
#define CELL_H

class cell {
  bool stair;
protected:
  int row, col;
  char display;
public:
  cell(int row, int col, char display);
  void setStair();
  bool getStair() const;
};

#endif
