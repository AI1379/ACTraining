#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pll pair<ll, ll>
void solve() {
  static ll n, k, cur, neg, ans;
  cin >> n >> k;
  vector<ll> a(n), b(n);
  for (auto &x : a)
    cin >> x;
  for (auto &x : b)
    cin >> x;
  vector<pll> v;
  v.reserve(2 * n);
  for (auto x : a)
    v.emplace_back(x, 1);
  for (auto x : b)
    v.emplace_back(x, 2);
  sort(v.begin(), v.end());
  cur = n;
  ans = neg = 0;
  for (int i = 0; i < 2 * n;) {
    auto [p, t] = v[i];
    if (neg <= k)
      ans = max(ans, p * cur);
    while (i < 2 * n && v[i].first == p) {
      if (v[i].second == 1) {
        ++neg;
      } else if (v[i].second == 2) {
        --cur;
        --neg;
      }
      ++i;
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
2 0
2 1
3 4
1 1
2
5
3 3
1 5 2
3 6 4
4 3
2 3 2 8
3 7 3 9
3 1
2 9 5
12 14 9

2
5
9
14
15
*/