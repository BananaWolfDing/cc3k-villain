#ifndef CELL_H
#define CELL_H

#include <vector>
class player;
class enemy;

class cell {
  bool stair;
  bool isCha = false;
protected:
  int row, col;
  char display;
  bool empty;
  std::vector<cell *> neighbour;
  player *PC;
public:
  cell(int row, int col, char display = '.');
  void setPC(player *PC);
  void setStair();
  void setRow(int r);
  void setCol(int c);
  void setNeighbour(std::vector<cell *> n);
  void addNeighbour(cell *c);

  bool isCharacter() const;
  bool getEmpty() const;
  bool getStair() const;
  int getRow() const;
  int getCol() const;
  std::vector<cell *> getNeighbour() const;

  enemy *getGuardian() const {return nullptr}
  int getAmount() const {return 0}
  std::string getName() const {return "";}
  void use() const {}
  std::string getRace() const {return "";}
  int getHp() const {return 0;}
  void die() const {}
  void setGuardian() {}
};

#endif
