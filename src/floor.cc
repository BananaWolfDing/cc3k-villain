#include "floor.h"
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <utility>

void inGrid(int x, int y) {
  return x >= 0 && x < gridHeight && y >= 0 && y < gridWidth;
}

void linkCells(cell *x, cell *y) {
  x.addNeighbour(y);
  y.addNeighbour(x);
}

void buildGrid(std::vector<std::vector<cell *>> &grid,
         const std::vector<std::vector<std::pair<int, int>>> chambers) {
  for (int i = 0; i < chamberNum; i++) {
    int n = chambers[i].size();
    for (int j = 0; j < n; j++) {
      int r = chamber[i][j].first;
      int c = chamber[i][j].second
      grid[r][c] = new cell(r, c);
      grid[r][c].setPC(PC);
    }
  }

  for (int i = 0; i < gridHeight; i++)
    for (int j = 0; j < gridWidth; j++) {
      if (inGrid(i, j + 1) && grid[i][j + 1] != nullptr)
        linkCells(grid[i][j], grid[i][j + 1]);
      if (inGrid(i + 1, j) && grid[i + 1][j] != nullptr)
          linkCells(grid[i][j], grid[i + 1][j]);
    }
}

void floor::createPlayer(player *PC) {
  int n = rand() % chamberNum;
  chambers[n].setPC(PC);
}

void floor::createStair() {
  int n = rand() % chamberNum;
  while (chambers[n].playerRoom())
    n = rand() % chamberNum;

  cell *c = chambers[n].createStair();
  grid[c->getRow()][c->getCol()] = c;
}

void floor::createPotion() {
  for (int i = 0; i < potionNum; i++) {
    int n = rand() % chamberNum;
    cell *c;
    int p = rand() % potionKinds;

    switch (p) {
      case 0: c = chambers[n].createBA();
      case 1: c = chambers[n].createBD();
      case 2: c = chambers[n].createPH();
      case 3: c = chambers[n].createRH();
      case 4: c = chambers[n].createWA();
      case 5: c = chambers[n].createWD();
    }

    grid[c->getRow()][c->getCol()] = c;
  }
}

void floor::createGold() {
  for (int i = 0; i < goldNum; i++) {
    int n = rand() % chamberNum;
    cell *c;
    int g = rand() % goldKinds;

    switch (g) {
      case 0: c = chambers[n].createGold(1);
      case 1: c = chambers[n].createGold(2)
      case 2: c = chambers[n].createGold(4)
      case 3: c = chambers[n].createGold(6)
    }

    grid[c->getRow()][c->getCol()] = c;
  }
}

void floor::createEnemy() {
  for (int i = 0; i < goldNum; i++) {
    int n = rand() % chamberNum;
    cell *c;
    int e = rand() % enemyKinds + 1;

    if (e <= PHuman)
      c = chambers[n].createHuman();
    else if (e <= PDwarf)
      c = chambers[n].createDwarf();
    else if (e <= PHalfling)
      c = chambers[n].createHalfling();
    else if (e <= PElf)
      c = chambers[n].createElf();
    else if (e <= POrc)
      c = chambers[n].createOrc();
    else if (e <= PMerchant)
      c = chambers[n].createMerchant();

    grid[c->getRow()][c->getCol()] = c;
  }
}

floor::floor(std::vector<std::vector<char>> map, std::string PCRace, player *PC):
    map{map}, freezeEnemy{false}, PC{PC} {
  std::vector<std::vector<std::pair<int, int>>> chamberCell;
  findChamber(map, chamberCell);
  buildGrid(grid, chamberCell);
  for (int i = 0; i < chamberNum; i++) {
    chamber *cham = new chamber;
    for (auto itr = chamber[i].begin(); itr != chamber[i].end(); itr++)
      cham.addCell(itr);
    chambers.push_back(cham);
  }

  srand(time(NULL));
  createPlayer(PC);
  createStair();
  createPotion();
  createGold();
  createEnemy();
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

  if (map[aimX][aimY] == "+" || map[aimX][aimY] == "#" || map[aimX][aimY] == ".") {
    PC->setRow(aimX);
    PC->setCol(aimY);
    action = "PC moves" + formal[dirIndex(dir)];
  }
  else if (map[aimX][aimY] == "G" && grid[aimX][aimY]->getGuard() == nullptr) {
    PC->setRow(aimX);
    PC->setCol(aimY);
    action = "PC moves " + formal[dirIndex(dir)] + " and picked some gold worth "
           + grid[aimX][aimY].getAmount();

    cell *c = new cell(aimX, aimY);

  }
  else
    return "Way blocked by a " + grid[aimX][aimY].getName() + "!";

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
    grid[aimX][aimY]->use();
    cell *c = new cell(aimX, aimY);
    delete grid[aimX][aimY];
    grid[aimX][aimY] = c;
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
  else if (!grid[aimX][aimY]->isCharacter())
    return "There is no enemy in " + formal[dirIndex(dir)];
  else {
    int damage = PC.attack(*grid[aimX][aimY]);
    action = "PC attacks " + grid[aimX][aimY]->getRace();
    if (damage)
      action += " and deals " + to_string(damage) + " damage";
    else
      action += " but missed";
    if (grid[aimX][aimY]->getHp() == 0) {
      grid[aimX][aimY]->die();
      action += " and killed it";
      for (auto itr = enemies.begin(); itr != enemies.end(); itr++)
        if (*itr == *grid[aimX][aimY])
          enemies.erase(itr);
      delete grid[aimX][aimY];
    }

    action += "!";
  }

  return action;
}

void floor::PCTurn(std::string command) {
  std::string action = "";

  if (command == "f") {
    if (freeze)
      action = "Enemies unfreezed!"
    else
      action = "Enemies freezed!";
    freeze = !freeze;
  }
  else if (command == "no" || command == "ne" || command == "ea" || command == "se"
        || command == "so" || command == "sw" || command == "we" || command == "nw")
    PCMove(command);
  else {
    istringstream iss{command};
    string movement;
    string dir;
    iss >> movement >> dir;
    if (movement == "u")
      action = PCUsePotion(dir);
    else if (movement == "a")
      action = PCAttack(dir);
    else
      action = "Command not found!";
  }
}

bool enemyCompare(enemy *a, enemy *b) {
  return (a->getRow() < b->getRow()) ||
         (a->getRow() == b->getRow() && a->getCol() < b->getCol());
}

void floor::enemyTurn() {
  std::string action = "";
  std::sort(enemies.begin(), enemies.end(), enemyCompare);
  for (auto itr = enemies.begin(); itr != enemies.end(); itr++) {
    if (std::abs(PC->getRow() - itr->getRow()) <= 1 &&
        std::abs(PC->getCol() - itr->getCol()) <= 1) {
      int damage = itr->attack(*PC);
      action += itr->getRace() + " attacks PC";
      if (damage)
        action += " and deals " + to_string(damage) + " damage."
      else
        action += " but missed."
    }
    else if (itr->getRace() != "dragon") {
      if (freezeEnemy()) continue;
      std::vector<cell *> possibleMoves;
      int x = itr->getRow();
      int y = itr->getCol();
      for (int i = 0; i < 8; i++)
        if (inGrid(x + XMove[i], y + YMove[i]) && map[x + XMove[i]][y + YMove[i]] == '.')
          possibleMoves.push_back(grid[x + XMove[i]][y + YMove[i]]);

        int s = possibleMoves.size();
        if (s) {
          srand(time(NULL));
          cell *c = possibleMoves[rand() % s];
          std::swap(grid[itr->getRow()][itr->getCol()], grid[c->getRow()][c->getCol()]);
          std::swap(map[itr->getRow()][itr->getCol()], map[c->getRow()][c->getCol()]);
          int tmpX = c->getRow(), tmpY = c->getCol();
          c->setRow(itr->getRow());
          c->setCol(itr->getCol());
          itr->setRow(tmpX);
          itr->setCol(tmpY);
        }
    }
    else {
      if (freezeEnemy()) continue;
      std::vector<cell *> possibleMoves;
      for (int i = -1; i <= 1; i++)
        for (int j = -1; j <= 1; j++) {
          int x = itr->getGuard()->getRow() + i;
          int y = itr->getGuard()->getCol() + j;
          if (inGrid(x, y) && map[x][y] == '.' &&
              std::abs(x - itr->getRow()) <= 1 && std::abs(y - itr->getCol()) <= 1)
            possibleMoves.push_back(grid[x + XMove[i]][y + YMove[i]]);
        }

        int s = possibleMoves.size();
        if (s) {
          srand(time(NULL));
          cell *c = possibleMoves[rand() % s];
          std::swap(grid[itr->getRow()][itr->getCol()], grid[c->getRow()][c->getCol()]);
          std::swap(map[itr->getRow()][itr->getCol()], map[c->getRow()][c->getCol()]);
          int tmpX = c->getRow(), tmpY = c->getCol();
          c->setRow(itr->getRow());
          c->setCol(itr->getCol());
          itr->setRow(tmpX);
          itr->setCol(tmpY);
        }
    }
}

void floor::draw() {
  for (int i = 0; i < gridHeight; i++) {
    for (int j = 0; j < gridWidth; j++)
      if (i == PC->getRow() && j == PC->getCol())
        std::cout << '@';
      else
        std::cout << map[i][j];
    std::cout << std::endl;
  }
}
