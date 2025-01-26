#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pll pair<ll, ll>
const ll INF = 1ll << 62;
void solve() {
  ll n;
  cin >> n;
  vector<pll> val(n);
  vector<array<bool, 5>> dp(n);
  for (auto i = 0; i < n; ++i)
    cin >> val[i].first;
  for (auto j = 0; j < n; ++j)
    cin >> val[j].second;
  sort(val.begin(), val.end(), [](pll lhs, pll rhs) {
    return min(lhs.first, lhs.second) < min(rhs.first, rhs.second);
  });
  dp[0][1] = dp[0][4] = true;
  for (auto i = 1; i < n; ++i) {
    if (val[i - 1].first < val[i].first && val[i - 1].second < val[i].second) {
      dp[i][1] |= dp[i - 1][1];
      dp[i][2] |= dp[i - 1][4];
      dp[i][3] |= dp[i - 1][3];
      dp[i][4] |= dp[i - 1][2];
    }
    if (val[i - 1].first < val[i].second && val[i - 1].second < val[i].first) {
      dp[i][1] |= dp[i - 1][2];
      dp[i][2] |= dp[i - 1][3];
      dp[i][3] |= dp[i - 1][4];
      dp[i][4] |= dp[i - 1][1];
    }
  }
  cout << ((dp[n - 1][1] || dp[n - 1][2]) ? "YES" : "NO") << endl;
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
