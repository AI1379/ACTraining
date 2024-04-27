#include <functional>
#include <iostream>
#include <map>
#include <utility>
#include <vector>
using namespace std;
#define ll long long
#define pll pair<ll, ll>
const ll MAXN = 100010;
const ll MOD = 998244353;
ll n, e;
pll edges[MAXN];
map<pll, ll> w;
vector<ll> tr[MAXN];
ll dep[MAXN], fa[MAXN], top[MAXN], pref[MAXN], siz[MAXN];
int main() {
  cin >> n;
  for (int i = 1; i <= n - 1; ++i) {
    cin >> edges[i].first >> edges[i].second;
    tr[edges[i].first].push_back(edges[i].second);
    tr[edges[i].second].push_back(edges[i].first);
  }
  cin >> e;
  e = e * n % MOD;
  function<void(int)> dfs1 = [&](int u) -> void {
    siz[u] = 1;
    for (auto v : tr[u]) {
      if (v == fa[u])
        continue;
      dep[v] = dep[u] + 1;
      fa[v] = u;
      dfs1(v);
      siz[u] += siz[v];
      pref[u] = siz[pref[u]] < siz[v] ? v : pref[u];
    }
  };
  function<void(int, int)> dfs2 = [&](int u, int c) -> void {
    top[u] = c;
    if (pref[u])
      dfs2(pref[u], c);
    for (auto v : tr[u]) {
      if (v == fa[u] || v == pref[u])
        continue;
      dfs2(v, v);
    }
  };
  function<int(int, int)> lca = [&](int u, int v) -> int {
    while (top[u] != top[v]) {
      if (dep[top[u]] < dep[top[v]])
        swap(u, v);
      u = fa[top[u]];
    }
    return dep[u] > dep[v] ? v : u;
  };
  function<int(int, int)> dis = [&](int u, int v) -> int {
    auto l = lca(u, v);
    return dep[u] + dep[v] - 2 * dep[l];
  };
  ll p = 0, q = 0;
  ll maxdep = 0;
  function<void(int, int)> getd = [&](int u, int d) {
    if (d > maxdep) {
      maxdep = d;
      q = u;
    }
    for (auto v : tr[u]) {
      if (v == fa[u])
        continue;
      getd(v, d + 1);
    }
  };
  dep[1] = 1;
  dfs1(1);
  dfs2(1, 1);
  for (auto i = 1; i <= n; ++i)
    if (dep[p] < dep[i])
      p = i;
  getd(p, 1);
  auto sum = 0ll;
  for (auto i = 1; i <= n; ++i) {
    sum = (sum + max(dis(i, p), dis(i, q))) % MOD;
  }
  auto qpow = [](ll a, ll b) {
    ll res = 1;
    while (b) {
      if (b % 2 == 1)
        res = res * a % MOD;
      a = a * a % MOD;
      b >>= 1;
    }
    return res;
  };
  if (sum == 0) {
    auto inv = qpow(n + 2, MOD - 2);
    auto h = e * inv % MOD;
    for (int i = 1; i <= n - 1; ++i) {
      if (edges[i].first == p || edges[i].second == p || edges[i].first == q ||
          edges[i].second == q) {
        cout << h + 1 << endl;
      } else {
        cout << 1 << endl;
      }
    }
  } else if (e == 0) {
    for (int i = 1; i <= n - 1; ++i) {
      cout << MOD << endl;
    }
  } else {
    auto invsum = qpow(sum, MOD - 2);
    auto res = invsum * e % MOD;
    for (int i = 1; i <= n - 1; ++i) {
      cout << res << endl;
    }
  }
  return 0;
}
