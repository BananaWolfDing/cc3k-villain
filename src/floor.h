#ifndef FLOOR_H
#define FLOOR_H

#include <string>
#include <ctime>
#include <cstdio>
#include <utility>
#include <cstdlib>
#include "cell.h"
#include "chamber.h"

class floor {
    std::vector<std::vector<char>> map;
    std::vector<std::vector<cell *>> grid;
    std::vector<chamber *> chambers;
    std::vector<cell *> enemies;
    bool freezeEnemy;
    bool givenFullMap;
    std::string PCMove(std::string dir);
    std::string PCUsePotion(std::string dir);
    std::string PCAttack(std::string dir);
    player *PC;
    int whichFloor;

    void buildGrid(const std::vector<std::vector<std::pair<int, int>>> chambers);
    void createPlayer(player *PC);
    void createStair();
    void createPotion();
    void createGold();
    void createEnemy();
public:
    floor(std::vector<std::vector<char>> map, player *PC, int floorNum, bool mapGiven);
    ~floor();
    bool passedFloor() const;
    std::string PCTurn(std::string command);
    std::string enemyTurn();
    void paint(std::string action) const;
};

#endif
