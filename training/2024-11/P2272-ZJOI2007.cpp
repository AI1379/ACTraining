#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pll pair<ll, ll>

constexpr ll MAXN = 100010;
ll n, m, mod;
vector<ll> graph[MAXN];
ll stk[MAXN], top = 0;
bool instk[MAXN];
ll dfn[MAXN], low[MAXN], idx = 0;
ll scc[MAXN], cnt = 0, sccsize[MAXN];
vector<ll> dag[MAXN];
ll deg[MAXN];
map<pll, bool> mp;
ll dp[MAXN], dpc[MAXN];
ll k, c;

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
      ++sccsize[cnt];
      scc[stk[top]] = cnt;
      instk[stk[top]] = false;
      --top;
    }
  }
}

void buildDAG() {
  for (int u = 1; u <= n; ++u) {
    for (auto v : graph[u]) {
      if (scc[u] != scc[v] && !mp[{scc[u], scc[v]}]) {
        mp[make_pair(scc[u], scc[v])] = true;
        dag[scc[u]].emplace_back(scc[v]);
        ++deg[scc[v]];
      }
    }
  }
}

void dagrun() {
  queue<ll> q;
  for (int u = 1; u <= cnt; ++u) {
    if (!deg[u]) {
      dp[u] = sccsize[u];
      dpc[u] = 1;
      q.push(u);
      k = max(dp[u], k);
    }
  }
  while (!q.empty()) {
    auto u = q.front();
    q.pop();
    for (auto v : dag[u]) {
      --deg[v];
      if (!deg[v])
        q.push(v);
      if (dp[v] == dp[u] + sccsize[v]) {
        dpc[v] = (dpc[v] + dpc[u]) % mod;
      } else if (dp[v] < dp[u] + sccsize[v]) {
        dp[v] = dp[u] + sccsize[v];
        dpc[v] = dpc[u];
      }
      k = max(k, dp[v]);
    }
  }
  for (int i = 1; i <= cnt; ++i) {
    if (dp[i] == k) {
      c = (c + dpc[i]) % mod;
    }
  }
}

int main() {
  ll u, v;
  ios::sync_with_stdio(false);
  cin >> n >> m >> mod;
  for (int i = 1; i <= m; ++i) {
    cin >> u >> v;
    graph[u].emplace_back(v);
  }
  for (int i = 1; i <= n; ++i) {
    if (!scc[i])
      tarjan(i);
  }
  buildDAG();
  dagrun();
  cout << k << endl << c << endl;
  return 0;
}