#include <vector>
#include <utility>
#include "findChamber.h"

bool chamberType(const char c) {
  return c != ' ' && c != '#' && c != '+' && c != '|' && c != '-';
}

bool valid(const int x, const int y, const std::vector<std::vector<char>> &map,
           const std::vector<std::vector<bool>> &visited) {
  int n = map.size();
  int m = map[0].size();
  return (x >= 0 && x < n) && (y >= 0 && y < m) &&
         (!visited[x][y]) && chamberType(map[x][y]);
}

void dfs(const int x, const int y, const std::vector<std::vector<char>> &map,
         std::vector<std::vector<bool>> &visited,
         std::vector<std::pair<int, int>> &ans) {
  visited[x][y] = true;
  ans.emplace_back(std::make_pair(x, y));

  if (valid(x - 1, y, map, visited)) dfs(x - 1, y, map, visited, ans);
  if (valid(x + 1, y, map, visited)) dfs(x + 1, y, map, visited, ans);
  if (valid(x, y - 1, map, visited)) dfs(x, y - 1, map, visited, ans);
  if (valid(x, y + 1, map, visited)) dfs(x, y + 1, map, visited, ans);
}

void findChamber(std::vector<std::vector<char>> map, std::vector<std::vector<std::pair<int, int>>> &chamber) {
  int n = map.size();
  int m = map[0].size();

  std::vector<std::vector<bool>> visited(n, std::vector<bool>(m));
  for (int i = 0; i < n; i++)
    for (int j = 0; j < m; j++)
      if (valid(i, j, map, visited)) {
        std::vector<std::pair<int, int>> c;
        dfs(i, j, map, visited, c);
        chamber.emplace_back(c);
      }
}
