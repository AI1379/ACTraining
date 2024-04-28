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
vector<ll> tr[MAXN];
ll dis1[MAXN], dis2[MAXN];
int main() {
  cin >> n;
  for (int i = 1; i <= n - 1; ++i) {
    cin >> edges[i].first >> edges[i].second;
    tr[edges[i].first].push_back(edges[i].second);
    tr[edges[i].second].push_back(edges[i].first);
  }
  cin >> e;
  e = e * n % MOD;
  ll p = 0, q = 0;
  ll maxdep = 0;
  function<void(int, int, int)> dfs1 = [&](int u, int f, int d) {
    if (d > maxdep) {
      p = u;
      maxdep = d;
    }
    for (auto v : tr[u]) {
      if (v == f)
        continue;
      dfs1(v, u, d + 1);
    }
  };
  dfs1(1, 0, 1);
  q = p;
  maxdep = 0;
  dfs1(q, 0, 1);
  auto sum = 0ll;
  function<void(int, int, ll *)> getdis = [&](int u, int f, ll *dis) {
    for (auto v : tr[u]) {
      if (v == f)
        continue;
      dis[v] = dis[u] + 1;
      getdis(v, u, dis);
    }
  };
  getdis(p, 0, dis1);
  getdis(q, 0, dis2);
  // cout << p << ' ' << q << endl;
  // for (auto i = 1; i <= n; ++i) {
  // cout << i << ' ' << dis1[i] << ' ' << dis2[i] << endl;
  // }
  for (auto i = 1; i <= n; ++i) {
    sum = (sum + max(dis1[i], dis2[i])) % MOD;
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
  if (n == 2) {
    auto inv = qpow(2, MOD - 2);
    if (e != 0)
      cout << e * inv % MOD << endl;
    else
      cout << MOD << endl;
  } else if (sum == 0) {
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
