#ifndef FIND_CHAMBER_H
#define FIND_CHAMBER_H

void findChamber(std::vector<std::vector<bool>> map, std::vector<std::vector<std::pair<int, int>>> &chamber);
/* This function will assume the map is valid and contains exactly 5 chambers and
   create a vector containing 5 vectors which consists of cells in same chambers. */

#endif
