#ifndef CHAMBER_H
#define CHAMBER_H

#include <vector>
#include <utility>
#include "cell.h"
#include "character/allCharacters.h"
#include "item/allItems.h"

class chamber {
  bool playerHere = false;
  int PCBornRow;
  int PCBornCol;
  std::vector<std::vector<cell *>> cells;
  cell *randomCell();
public:
  void addCell(cell *c);
  bool playerRoom() const;
  cell *createStair();

  cell *createHuman();
  cell *createDwarf();
  cell *createHalfling();
  cell *createElf();
  cell *createOrc();
  cell *createMerchant();
  cell *createDragon(cell *treasure);

  cell *createDrow();
  cell *createGoblin();
  cell *createShade();
  cell *createTroll();
  cell *createVampire();

  cell *createBA();
  cell *createBD();
  cell *createPH();
  cell *createRH();
  cell *createWA();
  cell *createWD();

  cell *createGold(int amount);
};

#endif
