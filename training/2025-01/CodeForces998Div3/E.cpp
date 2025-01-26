#include <bits/stdc++.h>
#include <iostream>
using namespace std;
#define ll long long
#define pll pair<ll, ll>
const ll INF = 1ll << 62;
void solve() {
  ll n, m1, m2, u, v, ans = 0;
  cin >> n >> m1 >> m2;
  vector<pll> E(m1), F(m2);
  vector<ll> G(n + 1), H(n + 1);
  for (int i = 1; i <= n; ++i) {
    H[i] = G[i] = i;
  }
  function<ll(vector<ll> &, ll)> find = [&](vector<ll> &S, ll x) {
    return S[x] == x ? x : S[x] = find(S, S[x]);
  };
  auto merge = [&](vector<ll> &S, ll x, ll y) {
    if (find(S, x) != find(S, y))
      S[find(S, x)] = find(S, y);
  };
  for (int i = 1; i <= m1; ++i) {
    cin >> u >> v;
    E.emplace_back(u, v);
  }
  for (int i = 1; i <= m2; ++i) {
    cin >> u >> v;
    merge(G, u, v);
    F.emplace_back(u, v);
  }
  for (auto [u, v] : E) {
    if (find(G, u) != find(G, v))
      ++ans;
    else
      merge(H, u, v);
  }
  for (auto [u, v] : F) {
    if (find(H, u) != find(H, v)) {
      merge(H, u, v);
      ++ans;
    }
  }
  cout << ans << endl;
}
int main() {
  ll test_cases;
  ios::sync_with_stdio(false);
  cin >> test_cases;
  while (test_cases--) {
    solve();
  }
  return 0;
}
/*
5
3 2 1
1 2
2 3
1 3
2 1 1
1 2
1 2
3 2 0
3 2
1 2
1 0 0
3 3 1
1 2
1 3
2 3
1 2

3
0
2
0
2
*/