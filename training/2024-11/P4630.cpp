#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define w(x) (1 <= (x) && (x) <= n ? 1 : 0)
constexpr ll MAXN = 100010;
ll n, m;
vector<ll> graph[MAXN];
// round-square tree
// note the doubled size
vector<ll> rstree[MAXN * 2];

ll dfn[MAXN], low[MAXN], idx = 0;
ll stk[MAXN], top = 0;
ll vbcccnt = 0;

ll subsize[MAXN * 2];
ll dp[MAXN * 2];
ll ans = 0;

void tarjan(ll u, ll fa) {
  dfn[u] = low[u] = ++idx;
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
    vbcccnt++;
    while (stk[top + 1] != u) {
      rstree[vbcccnt + n].push_back(stk[top]);
      rstree[stk[top]].push_back(vbcccnt + n);
      top--;
    }
    rstree[fa].push_back(vbcccnt + n);
    if (fa != 0)
      rstree[vbcccnt + n].push_back(fa);
  }
}

void treedp(int rt) {
  auto dfs = [&](auto &&self, ll u, ll fa) -> void {
    for (auto v : rstree[u]) {
      if (v == fa)
        continue;
      self(self, v, u);
      ans += (subsize[u] - w(u)) * (subsize[rt] - subsize[u]);
    }
  };
  dfs(dfs, rt, 0);
}

int main() {
  ll u, v;
  ios::sync_with_stdio(false);
  cin >> n >> m;
  for (int i = 1; i <= m; i++) {
    cin >> u >> v;
    graph[u].push_back(v);
    graph[v].push_back(u);
  }
  for (int i = 1; i <= n; i++) {
    if (!dfn[i]) {
      tarjan(i, 0);
    }
  }

  auto calcsubsize = [&](auto &&self, ll u, ll fa) -> void {
    subsize[u] = w(u);
    for (auto v : rstree[u]) {
      if (v == fa)
        continue;
      self(self, v, u);
      subsize[u] += subsize[v];
    }
  };
  calcsubsize(calcsubsize, 0, 0);

  for (auto u : rstree[0]) {
    treedp(u);
  }
  cout << ans << endl;
  return 0;
}