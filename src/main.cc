#include "floor.h"
#include "readMap.h"
#include "character/allCharacters.h"
#include "item/allItems.h"
#include <string>
#include <iostream>
#include <cstdlib>

inline void gameOver() {
  std::cout << "You lose" << std::endl;
}

int main() {
  srand((unsigned)time(NULL));
  std::cout << "Hello, welcome to CC3K...(we will add some words here later)" << std::endl;
  std::cout << "First, choose your race among Drow, Goblin, Shade, Troll and Vampire" << std::endl;
  std::string race;
  player *PC;
  while (std::getline(std::cin, race))
    if (race == "Drow") {
      PC = new drow;
      break;
    }
    else if (race == "Goblin") {
      PC = new goblin;
      break;
    }
    else if (race == "Shade") {
      PC = new shade;
      break;
    }
    else if (race == "Troll") {
      PC = new troll;
      break;
    }
    else if (race == "Vampire") {
      PC = new vampire;
      break;
    }
    else
      std::cout << "Invalid input, please choose again." << std::endl;

  std::string command;
  for (int curFloor = 1; curFloor <= 5; curFloor++) {
    PC->reset();
    floor gameFloor(readMap("../map.txt"), PC, curFloor);
    gameFloor.paint("New floor!");
    while (std::getline(std::cin, command)) {
      std::string action = gameFloor.PCTurn(command);
      if (action == "?") continue;

      if (PC->getHp() == 0) {
        gameOver();
        return 0;
      }
      if (gameFloor.passedFloor()) break;
      action += "\n" + gameFloor.enemyTurn();

      if (PC->getHp() == 0) {
        gameOver();
        return 0;
      }

      gameFloor.paint(action);
    }
  }

  std::cout << "You win! Score: " << PC->getGold() << std::endl;
  return 0;
}
