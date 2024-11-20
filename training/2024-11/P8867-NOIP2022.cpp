#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pll pair<ll, ll>
constexpr ll MOD = 1e9 + 7;
constexpr ll MAXN = 500010;
ll n, m;
vector<ll> graph[MAXN];

ll dfn[MAXN], low[MAXN], idx = 0;
ll stk[MAXN], top = 0;
ll ebcc[MAXN], cnt = 0;

vector<ll> tree[MAXN];
ll ecnt[MAXN], vcnt[MAXN], subsz[MAXN];

// dp[u][0] suggests that no vertex in the subtree of u is colored
// dp[u][1] suggests that there is at least one vertex in the subtree of u is
// colored and there is a route from each colored vertex to u
ll dp[MAXN][2];
ll ans = 0;

ll qpow(ll a, ll b) {
  ll res = 1;
  while (b) {
    if (b & 1) {
      res = res * a % MOD;
    }
    a = a * a % MOD;
    b >>= 1;
  }
  return res;
}

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
      ebcc[stk[top]] = cnt;
      --top;
    }
  }
}

void buildtree() {
  // Note that repeated edges are allowed which will simplify the DP process
  for (int u = 1; u <= n; ++u) {
    ++vcnt[ebcc[u]];
    for (auto v : graph[u]) {
      if (ebcc[u] != ebcc[v]) {
        tree[ebcc[u]].emplace_back(ebcc[v]);
      } else {
        ++ecnt[ebcc[u]];
      }
    }
  }

  // divide the edge count by 2
  for (int i = 1; i <= cnt; ++i)
    ecnt[i] >>= 1;

  // count subtree size
  auto dfs = [&](auto &&self, ll u, ll fa) -> void {
    subsz[u] = ecnt[u];
    for (auto v : tree[u]) {
      if (v == fa)
        continue;
      self(self, v, u);
      subsz[u] += subsz[v] + 1;
    }
  };
  dfs(dfs, 1, 0);
}

void treedp() {
  auto dfs = [&](auto &&self, ll u, ll fa) -> void {
    dp[u][0] = qpow(2, ecnt[u]);
    dp[u][1] = qpow(2, ecnt[u] + vcnt[u]);
    for (auto v : tree[u]) {
      if (v == fa)
        continue;
      self(self, v, u);
      dp[u][0] = dp[u][0] * 2 * dp[v][0] % MOD;
      dp[u][1] = dp[u][1] * (dp[v][0] * 2 % MOD + dp[v][1]) % MOD;
    }
    dp[u][1] = ((dp[u][1] - dp[u][0]) % MOD + MOD) % MOD;
  };
  dfs(dfs, 1, 0);

  // special case: the root is colored
  ans = dp[1][1];
  for (int i = 2; i <= cnt; ++i) {
    // note that the edge connecting i and its parent is counted in dp[i][1]
    // so we need to subtract it
    ans = (ans + dp[i][1] * qpow(2, m - subsz[i] - 1)) % MOD;
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
  for (int i = 1; i <= n; ++i) {
    if (!dfn[i])
      tarjan(i, 0);
  }
  buildtree();
  treedp();
  cout << ans << endl;
  return 0;
}