#ifndef CONFIG_H
#define CONFIG_H

const int gridWidth = 80;
const int gridHeight = 25;
const int chamberNum = 5;
const int potionKinds = 6;
const int potionNum = 10;
const int goldKinds = 4;
const int goldNum = 10;
const int enemyKinds = 6; // Dragon excluded
const int enemyNum = 20;
const int PHuman = 4;
const int PDwarf = 7; // 7 = 4 + 3
const int PHalfling = 12; // 12 = 4 + 3 + 5
const int PElf = 14; // 14 = 4 + 3 + 5 + 2
const int POrc = 16; // 16 = 4 + 3 + 5 + 2 + 2
const int PMerchant = 18; // 18 = 4 + 3 + 5 + 2 + 2 + 2
const int PTotal = PHuman + PDwarf + PHalfling + PElf + POrc + PMerchant;

const std::string    formal[8] = {"North", "Northeast", "East", "Southeast", "South", "Southwest", "West", "Northwest"};
const std::string direction[8] = {"no"   , "ne"       , "ea"  , "se"       , "so"   , "sw"       , "we"  , "nw"       };
const int             XMove[8] = {0      , 1          , 1     , 1          , 0      , -1         , -1    , -1         };
const int             YMove[8] = {-1     , -1         , 0     , 1          , 1      , 1          , 0     , -1         };

int dirIndex(std::string dir) {
  for (int i = 0; i < 8; i++)
    if (direction[i] == dir) return i;

  return -1;
}

#endif
