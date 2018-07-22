#ifndef CELL_H
#define CELL_H

#include <vector>
#include <string>

class player;
class enemy;
class character;

class cell {
  bool stair;
protected:
  int row, col;
  char display;
  bool empty;
  bool isCha = false;
  std::vector<cell *> neighbour;
  player *PC;
public:
  cell(int row, int col, char display = '.');
  cell();
  void setPC(player *PC);
  void setStair();
  void setRow(int r);
  void setCol(int c);
  void setNeighbour(std::vector<cell *> n);
  void addNeighbour(cell *c);
  void removeNeighbour(cell *c);
  void replaceCell(cell *c);

  player *getPC() const;
  char getDisplay() const;
  bool isCharacter() const;
  bool getEmpty() const;
  bool getStair() const;
  int getRow() const;
  int getCol() const;
  std::vector<cell *> getNeighbour() const;

  enemy *getGuardian() const {return nullptr;}
  int getAmount() const {return 0;}
  std::string getName() const {return "";}
  void use() const {}
  std::string getRace() const {return "";}
  int getHp() const {return 0;}
  void die(player &) const {}
  void setGuardian(enemy *) {}
  int getAtk() const {return 0;}
  int defend(cell &) {return 0;}
  int attack(character &) {return 0;}
  cell *getGuard() const {return nullptr;}
};

#endif
