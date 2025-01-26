#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pll pair<ll, ll>
const ll INF = 1ll << 62;
void solve() {
  map<int, int> mp;
  int a[7];
  cin >> a[1] >> a[2] >> a[4] >> a[5];
  mp[a[1] + a[2]]++;
  mp[a[4] - a[2]]++;
  mp[a[5] - a[4]]++;
  auto ans = 0;
  for (auto x : mp) {
    ans = max(ans, x.second);
  }
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