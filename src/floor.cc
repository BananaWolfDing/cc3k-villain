#include "floor.h"

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

void floor::createPlayer() {
  int n = rand() % chamberNum;
  cell *c;

  switch (PCRace) {
    case "Drow": c = chambers[n].createDrow();
    case "Goblin": c = chambers[n].creatGoblin();
    case "Shade": c = chambers[n].creatShade();
    case "Troll": c = chambers[n].creatTroll();
    case "Vampire": c = chambers[n].creatVampire();
  }

  grid[c->getRow()][c->getCol()] = c;
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

floor::floor(std::vector<std::vector<char>> map, std::string PCRace): map{map}, freezeEnemy{false} {
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
  createPlayer();
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
  else if (map[aimX][aimY] == "G") {
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

  // To be finished
}

void floor::PCTurn(std::string command) {
  std::string action;

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
