#include "floor.h"
#include "character/allRaces.h"
#include "item/allItems.h"
#include <string>

int main() {
  std::cout << "Hello, welcome to CC3K...(we will add some words here later)" << std::endl;
  std::cout << "First, choose your race among Drow, Goblin, Shade, Troll and Vampire" << endl;
  std::string race;
  player *PC;
  while (std::getline(std::cin, race))
    switch (race) {
      case "Drow": PC = new drow;
      case "Goblin": PC = new goblin;
      case "Shade": PC = new shade;
      case "Troll": PC = new troll;
      case "Vampire": PC = new vampire;
      default: std::cout << "Invalid input, please choose again." << std::endl;
    }

  std::string command;
  for (int curFloor = 1; curFloor <= 5; curFloor++) {
    floor gameFloor(readMap("map.txt"), PC, curFloor);
    while (std::getline(std::cin, command)) {
      std::string action = gameFloor.PCTurn(command);
      if (command == "?") continue;

      if (PC->getHp() == 0) {
        gameOver();
        return 0;
      }
      if (PC->passedFloor()) break;
      gameFloor.enemyTurn();

      if (PC->getHp() == 0) {
        gameOver();
        return 0;
      }

      gameFloor.paint();
    }
  }

  std::cout << "You win! Score: " << PC->getGold() << std::endl;
  return 0;
}
