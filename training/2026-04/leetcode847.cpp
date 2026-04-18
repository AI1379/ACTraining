#include <bits/stdc++.h>
using namespace std;

#ifdef DEBUG
#define DOUT cerr
#else
#define DOUT \
  if constexpr (false) cerr
#endif

class Solution {
 public:
  struct State {
    int mask;
    int id;
    int dist;
  };
  bool vis[8192][20];
  int shortestPathLength(vector<vector<int>>& graph) {
    memset(vis, false, sizeof(vis));
    queue<State> q;
    int n = graph.size();
    for (int i = 0; i < n; ++i) {
      q.push({1 << i, i, 0});
    }
    while (!q.empty()) {
      auto [mask, u, dist] = q.front();
      DOUT << u << ' ' << mask << endl;
      q.pop();
      if (mask == (1 << n) - 1) return dist;
      for (auto v : graph[u]) {
        auto new_mask = mask | (1 << v);
        if (vis[new_mask][v]) continue;
        vis[new_mask][v] = true;
        q.push({new_mask, v, dist + 1});
      }
    }
    return 0;
  }
};

int main() {
  int n, m;
  int u, v;
  cin >> n >> m;
  vector<vector<int>> graph(n);
  while (m--) {
    cin >> u >> v;
    graph[u].emplace_back(v);
    graph[v].emplace_back(u);
  }
  Solution sol;
  cout << sol.shortestPathLength(graph) << endl;

  return 0;
}
/*
5 5
0 1
1 2
1 3
2 3
2 4

4 3
0 1
0 2
0 3

*/