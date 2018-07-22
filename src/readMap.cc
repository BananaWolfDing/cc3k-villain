#include "readMap.h"

std::vector<std::vector<char>> readMap(std::string givenMap) {
  std::vector<std::vector<char>> map;

  if (givenMap != "") {
    std::ifstream mapin(givenMap.c_str());

    std::string row;
    while (std::getline(mapin, row)) {
      std::vector<char> singleRow(row.begin(), row.end());
      map.push_back(singleRow);
    }

    mapin.close();
  }

  return map;
}
