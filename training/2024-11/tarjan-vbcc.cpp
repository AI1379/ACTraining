#include <bits/stdc++.h>
using namespace std;
#define ll long long
constexpr ll MAXN = 500010;
ll n, m;
vector<ll> graph[MAXN];

ll stk[MAXN], top = 0;
ll dfn[MAXN], low[MAXN], idx = 0;
ll cnt;
vector<ll> vbcclist[MAXN];

void tarjan(ll u, ll fa) {
  low[u] = dfn[u] = ++idx;
  stk[++top] = u;
  for (auto v : graph[u]) {
    if (!dfn[v]) {
      tarjan(v, u);
      low[u] = min(low[u], low[v]);
    } else if (v != fa) {
      low[u] = min(low[u], dfn[v]);
    }
  }
  if (low[u] == dfn[u]) {
    ++cnt;
    while (stk[top + 1] != u) {
      vbcclist[cnt].emplace_back(stk[top]);
      --top;
    }
  }
}

int main() {
  ll u, v;
  ios::sync_with_stdio(false);
  cin >> n >> m;
  for (int i = 1; i <= m; ++i) {
    cin >> u >> v;
    graph[u].emplace_back(v);
    graph[v].emplace_back(u);
  }
  for (int u = 1; u <= n; ++u) {
    if (!dfn[u])
      tarjan(u, 0);
  }
  cout << cnt << endl;
  for (int i = 1; i <= cnt; ++i) {
    cout << vbcclist[i].size() << ' ';
    for (auto j : vbcclist[i]) {
      cout << j << ' ';
    }
    cout << endl;
  }
  return 0;
}