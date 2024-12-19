#include <bits/stdc++.h>
using namespace std;
#define ll long long
ll t;
void solve() {
  ll m, a, b, c;
  ll ans = 0;
  cin >> m >> a >> b >> c;
  ans += min(a, m);
  ans += min(b, m);
  ans += min(c, 2 * m - min(a, m) - min(b, m));
  cout << ans << endl;
}
int main() {
  cin >> t;
  while (t--) {
    solve();
  }
  return 0;
}
/*
5
10 5 5 10
3 6 1 1
15 14 12 4
1 1 1 1
420 6 9 69

20
5
30
2
84

*/