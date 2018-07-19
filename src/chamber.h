#ifndef CHAMBER_H
#define CHAMBER_H

#include <vector>
#include <utility>
#include "cell.h"
#include "character/allCharacters.h"
#include "item/allItems.h"

class chamber {
  std::vector<std::vector<cell *>> cells;
public:
  void addCell(cell *c);
  cell *createStair();

  cell *createHuman();
  cell *createDwarf();
  cell *createHalfling();
  cell *createElf();
  cell *createOrc();
  cell *createMerchant();
  cell *createDragon(cell *treasure);

  cell *createBA();
  cell *createBD();
  cell *createPH();
  cell *createRH();
  cell *createWA();
  cell *createWD();

  cell *createGold(int amount);
};

#endif
