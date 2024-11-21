#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define w(x) (1 <= (x) && (x) <= n ? -1 : rstree[x].size())
#define sz(x) (x <= n ? 1 : 0)
constexpr ll MAXN = 100010;
ll n, m;
vector<ll> graph[MAXN];
// round-square tree
// note the doubled size
vector<ll> rstree[MAXN * 2];

ll dfn[MAXN], low[MAXN], idx = 0;
ll stk[MAXN], top = 0;
ll vbcccnt = 0;

ll s[MAXN];
ll rsize[MAXN * 2];
ll dp[MAXN * 2];
ll ans = 0;

void tarjan(ll u, ll fa) {
  dfn[u] = low[u] = ++idx;
  stk[++top] = u;
  if (graph[u].empty()) {
    vbcccnt++;
    rstree[vbcccnt + n].push_back(u);
    rstree[u].push_back(vbcccnt + n);
    return;
  }
  for (auto v : graph[u]) {
    if (!dfn[v]) {
      tarjan(v, u);
      low[u] = min(low[u], low[v]);
    } else if (v != fa) {
      low[u] = min(low[u], dfn[v]);
    }
  }
  if (low[u] >= dfn[fa] && fa) {
    vbcccnt++;
    while (stk[top + 1] != u) {
      rstree[vbcccnt + n].push_back(stk[top]);
      rstree[stk[top]].push_back(vbcccnt + n);
      top--;
    }
    if (fa) {
      rstree[fa].push_back(vbcccnt + n);
      rstree[vbcccnt + n].push_back(fa);
    }
  }
}

void treedp(int rt) {
  // cout << s[rt] << endl;
  auto dfs = [&](auto &&self, ll u, ll fa) -> void {
    rsize[u] = sz(u);
    for (auto v : rstree[u]) {
      if (v == fa)
        continue;
      self(self, v, u);
      ans += 2 * rsize[u] * w(u) * rsize[v];
      rsize[u] += rsize[v];
    }
    ans += 2 * rsize[u] * w(u) * (s[rt] - rsize[u]);
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
      rstree[0].push_back(i);
      tarjan(i, 0);
      s[i] = idx;
      idx = 0;
    }
  }

  // for (int i = 0; i <= n + vbcccnt; i++) {
  //   cout << i << ": ";
  //   for (auto u : rstree[i]) {
  //     cout << u << ' ';
  //   }
  //   cout << endl;
  // }

  for (auto u : rstree[0]) {
    treedp(u);
  }
  cout << ans << endl;
  return 0;
}