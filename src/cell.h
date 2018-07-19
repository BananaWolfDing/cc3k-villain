#ifndef CELL_H
#define CELL_H

class cell {
  bool stair;
protected:
  int row, col;
  char display;
  bool empty;
  std::vector<cell *> neighbour;
public:
  cell(int row, int col, char display = '.');
  void setStair();
  void setRow(int r);
  void setCol(int c);
  void setNeighbour(std::vector<cell *> n);
  void addNeighbour(cell *c);

  bool getEmpty() const;
  bool getStair() const;
  int getRow() const;
  int getCol() const;
  std::vector<cell *> getNeighbour() const;
};

#endif
