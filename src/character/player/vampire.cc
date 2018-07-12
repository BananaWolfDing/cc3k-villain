#include "vampire.h"

vampire::vampire(): character{50, 25, 25, "vampire", "@"} {}

void vampire::addHP(int inc) {
  hp += inc;
}
