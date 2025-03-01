#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pll pair<ll, ll>
const ll INF = 1ll << 62;
void solve() {
  ll n, m1, m2, u, v, ans = 0;
  cin >> n >> m1 >> m2;
  vector<pll> F(m1), G(m2);
  vector<ll> GSet(n + 1), FSet(n + 1);
  for (int i = 1; i <= n; ++i) {
    FSet[i] = GSet[i] = i;
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
    F.emplace_back(u, v);
  }
  for (int i = 1; i <= m2; ++i) {
    cin >> u >> v;
    merge(GSet, u, v);
    G.emplace_back(u, v);
  }
  for (auto [u, v] : F) {
    if (find(GSet, u) != find(GSet, v))
      ++ans;
    else
      merge(FSet, u, v);
  }
  for (auto [u, v] : G) {
    if (find(FSet, u) != find(FSet, v)) {
      merge(FSet, u, v);
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