#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pll pair<ll, ll>
const ll MAXN = 5010;
ll t;
ll n;
pll mp[MAXN];
ll ans = 0;
ll mx;
void solve() {
  ans = 0;
  mx = -(1ll << 60);
  cin >> n;
  for (int i = 1; i <= n; ++i)
    cin >> mp[i].first;
  for (int i = 1; i <= n; ++i)
    cin >> mp[i].second;
  for (int i = 1; i <= n; ++i) {
    ans += max(mp[i].first, mp[i].second);
    mx = max(mx, min(mp[i].first, mp[i].second));
  }
  cout << ans + mx << endl;
}
int main() {
  ios::sync_with_stdio(false);
  cin >> t;
  while (t--)
    solve();
  return 0;
}
/*
3
1
-10
5
3
1 2 3
10 -5 -3
4
2 8 5 3
1 10 3 4

-5
16
29

*/