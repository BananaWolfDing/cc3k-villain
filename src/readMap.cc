#include "readMap.h"

std::vector<std::vector<char>> readMap(std::string givenMap) {
  std::vector<std::vector<char>> map;

  if (givenMap != "") {
    std::ifstream mapin;
    mapin.open(givenMap.c_str());

    std::string row;
    while (std::getline(mapin, row)) {
      std::vector<char> singleRow(row.begin(), row.end());
      map.push_back(singleRow);
    }
  }

  return map;
}
