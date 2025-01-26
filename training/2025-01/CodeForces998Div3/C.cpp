#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pll pair<ll, ll>
const ll INF = 1ll << 62;
void solve() {
  ll n, s, x, tot = 0, ans;
  map<ll, ll> mp;
  cin >> n >> s;
  for (int i = 0; i < n; ++i) {
    cin >> x;
    mp[x]++;
  }
  for (auto [k, v] : mp) {
    if (mp.find(s - k) != mp.end()) {
      tot += min(v, mp.at(s - k));
    }
  }
  ans = tot / 2;
  cout << ans << '\n';
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

4
4 4
1 2 3 2
8 15
1 2 3 4 5 6 7 8
6 1
1 1 1 1 1 1
16 9
3 1 4 1 5 9 2 6 5 3 5 8 9 7 9 3

2
1
0
4


*/