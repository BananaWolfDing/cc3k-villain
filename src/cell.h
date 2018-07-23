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
  ~cell();
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

  virtual enemy *getGuardian() const {return nullptr;}
  virtual int getAmount() const {return 0;}
  virtual std::string getName() const {return "";}
  virtual void use() {}
  virtual std::string getRace() const {return "";}
  virtual int getHp() const {return 0;}
  virtual void die(player &) {}
  virtual void setGuardian(enemy *) {}
  virtual int getAtk() const {return 0;}
  virtual int defend(cell &) {return 0;}
  virtual int attack(cell &) {return 0;}
  virtual cell *getGuard() const {return nullptr;}
};

#endif
