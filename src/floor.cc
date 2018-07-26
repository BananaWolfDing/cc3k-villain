#include "floor.h"
#include "findChamber.h"
#include "config.h"
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <string>
#include <utility>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <sstream>

inline bool inGrid(int x, int y) {
  return x >= 0 && x < gridHeight && y >= 0 && y < gridWidth;
}

inline void linkCells(cell *x, cell *y) {
  x->addNeighbour(y);
  y->addNeighbour(x);
}


void floor::createPlayer(player *PC) {
  int n = rand() % chamberNum;
  chambers[n]->setPC(PC);
}

void floor::createStair() {
  int n = rand() % chamberNum;
  while (chambers[n]->playerRoom())
    n = rand() % chamberNum;

  cell *c = chambers[n]->createStair();
  map[c->getRow()][c->getCol()] = c->getDisplay();
}

void floor::createPotion() {
  for (int i = 0; i < potionNum; i++) {
    int n = rand() % chamberNum;
    int p = rand() % potionKinds;
    cell *c;

    if (p == 0)
      c = chambers[n]->createBA();
    else if (p == 1)
      c = chambers[n]->createBD();
    else if (p == 2)
      c = chambers[n]->createPH();
    else if (p == 3)
      c = chambers[n]->createRH();
    else if (p == 4)
      c = chambers[n]->createWA();
    else
      c = chambers[n]->createWD();

    map[c->getRow()][c->getCol()] = c->getDisplay();
    grid[c->getRow()][c->getCol()] = c;
  }
}

void floor::createGold() {
  for (int i = 0; i < goldNum; i++) {
    int n = rand() % chamberNum;
    int g = rand() % goldKinds;
    cell *c;

    if (g == 0)
      c = chambers[n]->createGold(1);
    else if (g == 1)
      c = chambers[n]->createGold(2);
    else if (g == 2)
      c = chambers[n]->createGold(4);
    else {
      c = chambers[n]->createGold(6);
      cell *d = chambers[n]->createDragon(c);
      map[d->getRow()][d->getCol()] = d->getDisplay();
      grid[d->getRow()][d->getCol()] = d;
      enemies.push_back(d);
    }

    map[c->getRow()][c->getCol()] = c->getDisplay();
    grid[c->getRow()][c->getCol()] = c;
  }
}

void floor::createEnemy() {
  for (int i = 0; i < enemyNum; i++) {
    int n = rand() % chamberNum;
    cell *c;
    int e = rand() % PTotal + 1;

    if (e <= PHuman)
      c = chambers[n]->createHuman();
    else if (e <= PDwarf)
      c = chambers[n]->createDwarf();
    else if (e <= PHalfling)
      c = chambers[n]->createHalfling();
    else if (e <= PElf)
      c = chambers[n]->createElf();
    else if (e <= POrc)
      c = chambers[n]->createOrc();
    else if (e <= PMerchant)
      c = chambers[n]->createMerchant();

    map[c->getRow()][c->getCol()] = c->getDisplay();
    grid[c->getRow()][c->getCol()] = c;
    enemies.push_back(c);
  }
}

floor::floor(std::vector<std::vector<char>> map, player *PC, int floorNum, bool mapGiven):
    map{map}, freezeEnemy{false}, PC{PC}, whichFloor{floorNum}, givenFullMap{mapGiven} {
  grid.resize(gridHeight, std::vector<cell *>(gridWidth));
  map.resize(gridHeight, std::vector<char>(gridWidth));
  std::vector<std::vector<std::pair<int, int>>> chamberCell;
  findChamber(map, chamberCell);
    buildGrid(chamberCell);
  for (int i = 0; i < chamberNum; i++) {
    chamber *cham = new chamber;
    for (auto itr = chamberCell[i].begin(); itr != chamberCell[i].end(); itr++)
      cham->addCell(grid[itr->first][itr->second]);
    chambers.push_back(cham);
  }

  createPlayer(PC);
  if(!givenFullMap) {
    createStair();
    createPotion();
    createGold();
    createEnemy();
  }
}

void floor::buildGrid(const std::vector<std::vector<std::pair<int, int>>> chambers) {
  for (int i = 0; i < chamberNum; i++) {
    int n = chambers[i].size();
    for (int j = 0; j < n; j++) {
      int r = chambers[i][j].first;
      int c = chambers[i][j].second;
      if(map[r][c] == '.') {
        grid[r][c] = new cell(r, c);
      } else if(map[r][c] == '0'){
        grid[r][c] = new restoreHealth();
      } else if(map[r][c] == '1'){
        grid[r][c] = new boostAttack();
      } else if(map[r][c] == '2') {
        grid[r][c] = new boostDefence();
      } else if(map[r][c] == '3') {
        grid[r][c] = new poisonHealth();
      } else if(map[r][c] == '4') {
        grid[r][c] = new woundAttack();
      } else if(map[r][c] == '5') {
        grid[r][c] = new woundDefence();
      } else if(map[r][c] == '6') {
        grid[r][c] = new gold(2);
      } else if(map[r][c] == '7') {
        grid[r][c] = new gold(1);
      } else if(map[r][c] == '8') {
        grid[r][c] = new gold(4);
      } else if(map[r][c] == '9') {
        grid[r][c] = new gold(6);
        for (int i = 0; i < 8; i++)
          if (inGrid(r + XMove[i], c + YMove[i]) && map[r + XMove[i]][c + YMove[i]] == 'D') {
            grid[r + XMove[i]][c + YMove[i]] = new dragon(grid[r][c]);
          }
      }
      map[r][c] = grid[r][c]->getDisplay();
      grid[r][c]->setPC(PC);
    }
  }

  for (int i = 0; i < gridHeight; i++)
    for (int j = 0; j < gridWidth; j++) {
      if (inGrid(i, j + 1) && grid[i][j] != nullptr && grid[i][j + 1] != nullptr)
        linkCells(grid[i][j], grid[i][j + 1]);
      if (inGrid(i + 1, j) && grid[i][j] != nullptr && grid[i + 1][j] != nullptr)
        linkCells(grid[i][j], grid[i + 1][j]);
      if (inGrid(i + 1, j + 1) && grid[i][j] != nullptr && grid[i + 1][j + 1] != nullptr)
        linkCells(grid[i][j], grid[i + 1][j + 1]);
      if (inGrid(i + 1, j - 1) && grid[i][j] != nullptr && grid[i + 1][j - 1] != nullptr)
        linkCells(grid[i][j], grid[i + 1][j - 1]);
    }
}

floor::~floor() {
  for (int i = 0; i < chamberNum; i++)
    delete chambers[i];

  for (int i = 0; i < gridHeight; i++)
    for (int j = 0; j < gridWidth; j++)
      delete grid[i][j];
}

bool floor::passedFloor() const {
  return map[PC->getRow()][PC->getCol()] == '\\';
}

std::string floor::PCMove(std::string dir) {
  int x = PC->getRow();
  int y = PC->getCol();
  int aimX = x + XMove[dirIndex(dir)];
  int aimY = y + YMove[dirIndex(dir)];
  std::string action = "";

  if (!inGrid(aimX, aimY))
    return "Invalid move!";

  if (map[aimX][aimY] == '-' || map[aimX][aimY] == '|' || map[aimX][aimY] == ' ')
    return "Way blocked by wall!";

  if (map[aimX][aimY] == '+' || map[aimX][aimY] == '#'
   || map[aimX][aimY] == '.' || map[aimX][aimY] == '\\') {
    PC->setRow(aimX);
    PC->setCol(aimY);
    action = "PC moves " + formal[dirIndex(dir)];
  }
  else if (map[aimX][aimY] == 'G' && grid[aimX][aimY]->getGuardian() == nullptr){
    PC->setRow(aimX);
    PC->setCol(aimY);
    action = "PC moves " + formal[dirIndex(dir)] + " and picked up gold worth "
                                                   + std::to_string(grid[aimX][aimY]->getAmount());
    grid[aimX][aimY]->use();
    cell *newCell = new cell(aimX, aimY);
    newCell->replaceCell(grid[aimX][aimY]);
    grid[aimX][aimY] = newCell;
    map[aimX][aimY] = grid[aimX][aimY]->getDisplay();
  }
  else if (map[aimX][aimY] == 'G' && grid[aimX][aimY]->getGuardian() != nullptr) {
    PC->setRow(aimX);
    PC->setCol(aimY);
    action = "PC moves " + formal[dirIndex(dir)] +
             " but have to defeat the dragon guarding the gold to pick it up.";
  }
  else
    return "Way blocked!";

  for (int i = 0; i < 8; i++) {
    int xx = aimX + XMove[i];
    int yy = aimY + YMove[i];
    if (inGrid(xx, yy)) {
      if (map[xx][yy] == 'P')
        action += " and see an unknown potion";
      if (map[xx][yy] == 'G')
        action += " and see some gold";
    }
  }

  return action + "!";
}

std::string floor::PCUsePotion(std::string dir) {
  int x = PC->getRow();
  int y = PC->getCol();
  int aimX = x + XMove[dirIndex(dir)];
  int aimY = y + YMove[dirIndex(dir)];

  if (!inGrid(aimX, aimY))
    return "Invalid direction!";
  else if (map[aimX][aimY] != 'P')
    return "There is no potion in " + formal[dirIndex(dir)];
  else {
    std::string p = grid[aimX][aimY]->getName();
    grid[aimX][aimY]->use();
    cell *newCell = new cell(aimX, aimY);
    grid[aimX][aimY] = newCell;
    newCell->replaceCell(grid[aimX][aimY]);
    map[aimX][aimY] = grid[aimX][aimY]->getDisplay();
    return "PC uses " + p;
  }
}

std::string floor::PCAttack(std::string dir) {
  int x = PC->getRow();
  int y = PC->getCol();
  int aimX = x + XMove[dirIndex(dir)];
  int aimY = y + YMove[dirIndex(dir)];
  std::string action = "";

  if (!inGrid(aimX, aimY))
    return "Invalid direction!";
  else if (map[aimX][aimY] == '-' || map[aimX][aimY] == '|' || map[aimX][aimY] == '+' ||
           map[aimX][aimY] == ' ' || map[aimX][aimY] == '#' || !grid[aimX][aimY]->isCharacter())
    return "There is no enemy in " + formal[dirIndex(dir)];
  else {
    action = PC->attack(*grid[aimX][aimY]);
    if (grid[aimX][aimY]->getHp() == 0) {
      std::string deadEnemy = grid[aimX][aimY]->getRace();
      grid[aimX][aimY]->die(*PC);
      action += " and killed it";
      for (auto itr = enemies.begin(); itr != enemies.end(); itr++)
        if (*itr == grid[aimX][aimY]) {
          enemies.erase(itr);
          break;
        }
        cell *newCell = new cell(aimX, aimY);
        newCell->replaceCell(grid[aimX][aimY]);
        grid[aimX][aimY] = newCell;
        map[aimX][aimY] = grid[aimX][aimY]->getDisplay();

      if(deadEnemy == "Merchant") {
        gold *newMerchantHoard = new gold(4);
        newMerchantHoard->replaceCell(grid[aimX][aimY]);
        grid[aimX][aimY] = newMerchantHoard;
        map[aimX][aimY] = grid[aimX][aimY]->getDisplay();
      }
      else if(deadEnemy == "Human") {
        gold *newHumanHoard = new gold(2);
        newHumanHoard->replaceCell(grid[aimX][aimY]);
        grid[aimX][aimY] = newHumanHoard;
        map[aimX][aimY] = grid[aimX][aimY]->getDisplay();

        std::vector<cell *> possibleMoves;
        for (int i = 0; i < 8; i++)
          if (inGrid(aimX + XMove[i], aimY + YMove[i]) && map[aimX + XMove[i]][aimY + YMove[i]] == '.' &&
                  (aimX + XMove[i] != PC->getRow() || aimY + YMove[i] != PC->getCol()))
            possibleMoves.push_back(grid[aimX + XMove[i]][aimY + YMove[i]]);

        int s = possibleMoves.size();
        if (s) {
          cell *c = possibleMoves[rand() % s];
          int xx = c->getRow();
          int yy = c->getCol();

          newHumanHoard = new gold(2);
          newHumanHoard->replaceCell(c);
          grid[xx][yy] = newHumanHoard;
          map[xx][yy] = grid[xx][yy]->getDisplay();
        }
      }
    }
    action += "!";
  }

  return action;
}

std::string floor::PCTurn(std::string command) {
  std::string action = "";

  if (command == "f") {
    if (freezeEnemy)
      action = "Enemies unfreezed!";
    else
      action = "Enemies freezed!";
    freezeEnemy = !freezeEnemy;
  }
  else if (command == "no" || command == "ne" || command == "ea" || command == "se"
        || command == "so" || command == "sw" || command == "we" || command == "nw")
    action = PCMove(command);
  else {
    std::istringstream iss{command};
    std::string movement;
    std::string dir;
    iss >> movement >> dir;
    if (movement == "u")
      action = PCUsePotion(dir);
    else if (movement == "a")
      action = PCAttack(dir);
    else
      action = "?";
  }

  return action;
}

inline bool enemyCompare(cell *a, cell *b) {
  return (a->getRow() < b->getRow()) ||
         (a->getRow() == b->getRow() && a->getCol() < b->getCol());
}

std::string floor::enemyTurn() {
  std::string action = "";
  std::sort(enemies.begin(), enemies.end(), enemyCompare);
  for (auto itr = enemies.begin(); itr != enemies.end(); itr++)
    if (std::abs(PC->getRow() - (*itr)->getRow()) <= 1 &&
        std::abs(PC->getCol() - (*itr)->getCol()) <= 1)
      action += (*itr)->attack(*PC);
    else if ((*itr)->getRace() == "Dragon") {
      if (std::abs(PC->getRow() - (*itr)->getGuard()->getRow()) <= 1 &&
          std::abs(PC->getCol() - (*itr)->getGuard()->getCol()) <= 1)
        action += (*itr)->attack(*PC);
    }
    else {
      if (freezeEnemy) continue;
      std::vector<cell *> possibleMoves;
      int x = (*itr)->getRow();
      int y = (*itr)->getCol();
      for (int i = 0; i < 8; i++)
        if (inGrid(x + XMove[i], y + YMove[i]) && map[x + XMove[i]][y + YMove[i]] == '.')
          possibleMoves.push_back(grid[x + XMove[i]][y + YMove[i]]);

      int s = possibleMoves.size();
      if (s) {
        cell *c = possibleMoves[rand() % s];
        int xx = c->getRow();
        int yy = c->getCol();

        cell *tmpCell = grid[xx][yy];
        grid[xx][yy] = grid[x][y];
        grid[x][y] = tmpCell;
        char tmpChar = map[xx][yy];
        map[xx][yy] = map[x][y];
        map[x][y] = tmpChar;

        int tmpX = c->getRow(), tmpY = c->getCol();
        c->setRow(x);
        c->setCol(y);
        (*itr)->setRow(tmpX);
        (*itr)->setCol(tmpY);
        }
      }

  return action;
}

inline void printAction(Xwindow *win, std::string action, int x, int y) {
  std::istringstream ss{action};

  std::string row;
  while (std::getline(ss, row)) {
    win->drawString(x, y, row);
    y += 20;
  }
}

void floor::paint(std::string action, Xwindow *win) const {
  win->fillRectangle(0, 0, 1000, 600, Xwindow::White);
  for (int i = 0; i <= gridHeight; i++)
    win->fillRectangle(0, i * (cellSize + 1), gridWidth * (cellSize + 1) + 1, 1, Xwindow::Black);

  for (int i = 0; i <= gridWidth; i++)
    win->fillRectangle(i * (cellSize + 1), 0, 1, gridHeight * (cellSize + 1) + 1, Xwindow::Black);

  for (int i = 0; i < gridHeight; i++)
    for (int j = 0; j < gridWidth; j++) {
      int x = i * (cellSize + 1) + 1;
      int y = j * (cellSize + 1) + 1;
      if (i == PC->getRow() && j == PC->getCol())
        win->fillRectangle(y, x, cellSize, cellSize, Xwindow::Blue);
      else if (map[i][j] == ' ')
        win->fillRectangle(y, x, cellSize, cellSize, Xwindow::Gray);
      else if (map[i][j] == '-' || map[i][j] == '|')
        win->fillRectangle(y, x, cellSize, cellSize, Xwindow::Black);
      else if (map[i][j] == '#' || map[i][j] == '+')
        win->fillRectangle(y, x, cellSize, cellSize, Xwindow::Green);
      else if (map[i][j] == 'G')
        win->fillRectangle(y, x, cellSize, cellSize, Xwindow::Gold);
      else if (map[i][j] == '.')
        win->fillRectangle(y, x, cellSize, cellSize, Xwindow::White);
      else if (map[i][j] == 'P')
        win->fillRectangle(y, x, cellSize, cellSize, Xwindow::Indigo);
      else if (map[i][j] == '\\')
        win->fillRectangle(y, x, cellSize, cellSize, Xwindow::Cyan);
      else {
        win->fillRectangle(y, x, cellSize, cellSize, Xwindow::Red);
        win->drawString(y + cellSize / 2, x + cellSize, std::string(1, map[i][j]));
      }
    }

  int textRow = gridHeight * (cellSize + 1) + 1;
  win->drawString(15, textRow + 20, "Race: " + PC->getRace());
  win->drawString(15, textRow + 40, "Gold: " + std::to_string(PC->getGold()));
  win->drawString(15, textRow + 60, "Floor: " + std::to_string(whichFloor));
  win->drawString(15, textRow + 80, "Hp: " + std::to_string(PC->getHp()));
  win->drawString(15, textRow + 100, "Atk: " + std::to_string(PC->getAtk()));
  win->drawString(15, textRow + 120, "Def: " + std::to_string(PC->getDef()));
  win->drawString(15, textRow + 140, "Action:");
  printAction(win, action, 15, textRow + 160);

  for (int i = 0; i < gridHeight; i++) {
    for (int j = 0; j < gridWidth; j++)
      if (i == PC->getRow() && j == PC->getCol())
        std::cout << '@';
      else
        std::cout << map[i][j];
    std::cout << std::endl;
  }

  std::cout << "Race: " << PC->getRace() << "   Gold: " << PC->getGold()
            << "                        Floor: " << whichFloor << std::endl;
  std::cout << "HP: " << PC->getHp() << std::endl;
  std::cout << "Atk: " << PC->getAtk() << std::endl;
  std::cout << "Def: " << PC->getDef() << std::endl;
  std::cout << "Action:\n" << action << std::endl;
}
