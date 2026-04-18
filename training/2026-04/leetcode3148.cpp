#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  int maxScore(vector<vector<int>>& grid) {
    vector<vector<int>> min_grid = grid;
    auto m = grid.size(), n = grid[0].size();
    for (auto i = 0ull; i < m; ++i) {
      for (auto j = 0ull; j < n; ++j) {
        if (i > 0) min_grid[i][j] = min(min_grid[i][j], min_grid[i - 1][j]);
        if (j > 0) min_grid[i][j] = min(min_grid[i][j], min_grid[i][j - 1]);
      }
    }
    int ans = 0x80000000;
    for (auto i = 0ull; i < m; ++i) {
      for (auto j = 0ull; j < n; ++j) {
        if (i > 0) ans = max(ans, grid[i][j] - min_grid[i - 1][j]);
        if (j > 0) ans = max(ans, grid[i][j] - min_grid[i][j - 1]);
      }
    }
    return ans;
  }
};

/*
2 8
1 4
4 7
3 1
9 5

*/
int main() { return 0; }