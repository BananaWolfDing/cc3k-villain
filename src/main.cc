#include "floor.h"
#include "readMap.h"
#include "character/allCharacters.h"
#include "item/allItems.h"
#include <string>
#include <iostream>
#include <cstdlib>

inline bool gameOver() {
  std::cout << "You lose" << std::endl;
  std::cout << "Enter 'r' to RESTART the game or enter 'q' to EXIT the game: " << std::endl;
  std::string command;
  while(std::getline(std::cin, command)){
    if(command == "q"){
      return false;
    }
    if(command == "r") {
      return true;
    }
  }
}

inline bool game(bool isMapGiven, std::string mapName) {
  std::cout << "Hello, welcome to CC3K...(we will add some words here later)" << std::endl;
  std::cout << "First, choose your race among Drow(d), Goblin(g), Shade(s), Troll(t) and Vampire(v)" << std::endl;
  std::string race;
  player *PC;
  while (std::getline(std::cin, race))
    if (race == "d") {
      PC = new drow;
      break;
    }
    else if (race == "g") {
      PC = new goblin;
      break;
    }
    else if (race == "s") {
      PC = new shade;
      break;
    }
    else if (race == "t") {
      PC = new troll;
      break;
    }
    else if (race == "v") {
      PC = new vampire;
      break;
    }
    else
      std::cout << "Invalid input, please choose again." << std::endl;

  std::string command;


  //std::vector<a>
  //std::vector<floor> [5]
  //for random create player on first floor
  // int i = 0;
  // while ( i < 5){}
    // if there is given map for 5 floor.
  if(isMapGiven == true) {
    std::cout << "true" << std::endl;
    std::vector<floor> floors;
    std::string row;
    std::vector<std::vector<char>> tmprows;
    std::cout << mapName << std::endl;
    std::ifstream mapin(mapName);
    for (int count = 0; count < 5; count++) {
      std::cout << "9" << std::endl;
      for (int i = 0; i < 25; i++) {
        std::cout << "2 ";
        std::getline(mapin, row);
        std::vector<char> singleRow(row.begin(), row.end());
        tmprows.push_back(singleRow);
      }

      floor tmpfloor(tmprows, PC, count, isMapGiven);
      std::cout << "7" << std::endl;
      floors.emplace_back(tmpfloor);
      count++;
    }
    for (int curFloor = 0; curFloor <= 4; curFloor++) {
      std::cout << "enter floor" << std::endl;
      PC->reset();
      floors[curFloor].paint("New floor!");
      while (std::getline(std::cin, command)) {
        if (command == "q")
          return false;
        if (command == "r")
          return true;
        std::string action = floors[curFloor].PCTurn(command);
        if (action == "?") {
          std::cout << "Invalid input" << std::endl;
          continue;
        }
        if (PC->getHp() == 0) {
          floors[curFloor].paint(action);
          return gameOver();
        }
        if (floors[curFloor].passedFloor()) break;
        action += "\n" + floors[curFloor].enemyTurn();
        if (PC->getHp() == 0) {
          floors[curFloor].paint(action);
          return gameOver();
        }
        floors[curFloor].paint(action);
      }
    }
  }

  else {
    for (int curFloor = 1; curFloor <= 5; curFloor++) {
      PC->reset();
      floor gameFloor(readMap(mapName), PC, curFloor, isMapGiven);
      gameFloor.paint("New floor!");
      while (std::getline(std::cin, command)) {
        if (command == "q")
          return false;
        if (command == "r")
          return true;
        std::string action = gameFloor.PCTurn(command);
        if (action == "?") {
          std::cout << "Invalid input" << std::endl;
          continue;
        }
        if (PC->getHp() == 0) {
          gameFloor.paint(action);
          return gameOver();
        }
        if (gameFloor.passedFloor()) break;
        action += "\n" + gameFloor.enemyTurn();
        if (PC->getHp() == 0) {
          gameFloor.paint(action);
          return gameOver();
        }
        gameFloor.paint(action);
      }
    }
  }

  std::cout << "You win! Score :" << PC->getGold() << std::endl;
  return false;
}

int main(int argc, char *argv[]) {
  //read in given digital map
  std::string fileName = "";
  if(argc > 1){
    fileName = argv[1];
    game(true,fileName);
  }
  else{
    srand((unsigned)time(NULL));
    while (game(false,"map.txt"))
      std::cout << "Game restart!" << std::endl;
    return 0;
  }
}
