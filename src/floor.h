#ifndef FLOOR_H
#define FLOOR_H

#include <string>
#include <ctime>
#include <cstdio>
#include <cstdlib>
#include "config.h"
#include "cell.h"
#include "findChamber.h"
#include "chamber.h"

class player;

class floor {
  std::vector<std::vector<char>> map;
  std::vector<std::vector<cell *>> grid;
  std::vector<chamber *> chambers;
  std::vector<enemy *> enemies;
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
public:
  floor(std::vector<std::vector<char>> map, std::string PCRace, player *PC);
  void PCTurn(std::string command);
  void enemyTurn();
  void paint() const;
};

#endif
