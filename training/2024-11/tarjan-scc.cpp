#include <bits/stdc++.h>
using namespace std;
#define ll long long
constexpr ll MAXN = 10010;

ll n, m;
vector<ll> graph[MAXN];
ll scc[MAXN], cnt = 0, sccsize[MAXN];
ll dfn[MAXN], low[MAXN], idx = 0;
ll stk[MAXN], top = 0;
bool instk[MAXN];
vector<ll> sccgraph[MAXN];

void tarjan(ll u) {
  low[u] = dfn[u] = ++idx;
  stk[++top] = u;
  instk[u] = true;
  for (auto v : graph[u]) {
    if (!dfn[v]) {
      tarjan(v);
      low[u] = min(low[u], low[v]);
    } else if (instk[v]) {
      low[u] = min(low[u], dfn[v]);
    }
  }
  if (low[u] == dfn[u]) {
    ++cnt;
    while (stk[top + 1] != u) {
      scc[stk[top]] = cnt;
      ++sccsize[cnt];
      instk[stk[top]] = false;
      --top;
    }
  }
}

int main() {
  int u, v;
  ios::sync_with_stdio(false);
  cin >> n >> m;
  for (int i = 1; i <= m; ++i) {
    cin >> u >> v;
    graph[u].emplace_back(v);
  }
  for (int i = 1; i <= n; ++i) {
    if (!dfn[i])
      tarjan(i);
  }
  for (int i = 1; i <= n; ++i) {
    for (auto j : graph[i]) {
      if (scc[i] != scc[j]) {
        sccgraph[scc[i]].emplace_back(scc[j]);
      }
    }
  }
  ll ans = 0;
  bool flag = true;
  for (int i = 1; i <= cnt; ++i) {
    if (sccgraph[i].empty()) {
      if (flag) {
        ans = sccsize[i];
        flag = false;
      } else {
        ans = 0;
        break;
      }
    }
  }
  cout << ans << endl;
  return 0;
}
