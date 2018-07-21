#include "floor.h"
#include "character/allRaces.h"
#include "item/allItems.h"
#include <string>

int main() {
  std::cout << "Hello, welcome to CC3K...(we will add some words here later)" << std::endl;
  std::cout << "First, choose your race among Drow, Goblin, Shade, Troll and Vampire" << endl;
  std::string race;
  player *PC;
  while (getline(std::cin, race))
    switch (race) {
      case "Drow": PC = new drow;
      case "Goblin": PC = new goblin;
      case "Shade": PC = new shade;
      case "Troll": PC = new troll;
      case "Vampire": PC = new vampire;
      default: std::cout << "Invalid input, please choose again." << std::endl;
    }

  
}
