#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pll pair<ll, ll>
const ll INF = 1ll << 62;
void solve() {
  ll n, m;
  cin >> n >> m;
  vector<vector<ll>> cards(n, vector<ll>(m));
  for (auto &row : cards) {
    for (auto &card : row) {
      cin >> card;
      card %= n;
    }
  }
  vector<ll> ans(n);
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m - 1; ++j) {
      if (cards[i][j] != cards[i][j + 1]) {
        cout << -1 << '\n';
        return;
      }
    }
    ans[cards[i][0]] = i + 1;
  }
  for (auto x : ans) {
    cout << x << ' ';
  }
  cout << '\n';
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
2 3
0 4 2
1 5 3
1 1
0
2 2
1 2
0 3
4 1
1
2
0
3

1 2
1
-1
3 1 2 4

*/