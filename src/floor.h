#ifndef FLOOR_H
#define FLOOR_H

#include <string>
#include <ctime>
#include <cstdio>
#include <cstdlib>
#include "cell.h"
#include "chamber.h"

class floor {
  std::vector<std::vector<char>> map;
  std::vector<std::vector<cell *>> grid;
  std::vector<chamber *> chambers;
  std::vector<cell *> enemies;
  void createPlayer(player *PC);
  void createStair();
  void createPotion();
  void createGold();
  void createEnemy();
  bool freezeEnemy;
  std::string PCMove(std::string dir);
  std::string PCUsePotion(std::string dir);
  std::string PCAttack(std::string dir);
  player *PC;
  int whichFloor;
public:
  floor(std::vector<std::vector<char>> map, player *PC, int floorNum);
  ~floor();
  bool passedFloor() const;
  std::string PCTurn(std::string command);
  void enemyTurn();
  void paint(std::string action) const;
};

#endif
