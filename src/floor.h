#ifndef FLOOR_H
#define FLOOR_H

#include <string>
#include <ctime>
#include <cstdio>
#include <cstdlib>
#include "config.h"
#include "cell.h"
#include "findChamber.h"

class floor {
  std::vector<std::vector<char>> map;
  std::vector<std::vector<cell *>> grid;
  std::vector<chamber *> chambers;
  player *PC;
  void createPlayer(std::string PCRace);
  void createStair();
  void createPotion();
  void createGold();
  void createEnemy();
  bool freezeEnemy;
  std::string PCMove(std::string dir);
  std::string PCUsePotion(std::string dir);
  std::string PCAttack(std::string dir);
public:
  floor(std::vector<std::vector<char>> map, std::string PCRace);
  void PCTurn(std::string command);
  void enemyTurn();
};

#endif
