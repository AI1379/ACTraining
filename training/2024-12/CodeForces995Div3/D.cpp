#include <bits/stdc++.h>
using namespace std;
#define ll long long
const ll MAXN = 500010;
ll test_cases;
ll n;
ll x, y, s, ans, l, r;
ll val[MAXN];
ll tmp[MAXN];
void solve() {
  ans = s = 0;
  cin >> n >> x >> y;
  for (int i = 1; i <= n; ++i) {
    cin >> val[i];
    s += val[i];
    tmp[i] = val[i];
  }
  // cout << s << ' ';
  sort(tmp + 1, tmp + n + 1);
  // for (int i = 1; i <= n; ++i) {
  // cout << tmp[i] << ' ';
  // }
  for (int i = 1; i <= n; ++i) {
    ans += upper_bound(tmp + 1, tmp + n + 1, s - val[i] - x) -
           lower_bound(tmp + 1, tmp + n + 1, s - val[i] - y);
    if (s - val[i] - y <= val[i] && val[i] <= s - val[i] - x)
      --ans;
    // cout << ans << ' ';
  }
  ans /= 2;
  cout << ans << endl;
}
int main() {
  ios::sync_with_stdio(false);
  cin >> test_cases;
  while (test_cases--) {
    solve();
  }
  return 0;
}
/*
7
4 8 10
4 6 3 6
6 22 27
4 9 6 3 4 5
3 8 10
3 2 1
3 1 1
2 3 4
3 3 6
3 2 1
4 4 12
3 3 2 1
6 8 8
1 1 2 2 2 3


4
7
0
0
1
5
6

*/