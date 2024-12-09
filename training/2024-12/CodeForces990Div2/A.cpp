#include <bits/stdc++.h>
using namespace std;
#define ll long long
ll t;
bool issquare(ll x) {
  ll y = sqrt(x);
  return y * y == x && y % 2 == 1;
}
void solve() {
  ll n, x, cur = 0, ans = 0;
  cin >> n;
  for (int i = 1; i <= n; ++i) {
    cin >> x;
    cur += x;
    ans += issquare(cur);
  }
  cout << ans << endl;
}
int main() {
  cin >> t;
  while (t--)
    solve();
  return 0;
}
/*
5
1
1
2
1 8
5
1 3 2 1 2
7
1 2 1 10 2 7 2
14
1 10 10 100 1 1 10 1 10 2 10 2 10 1

1
2
2
2
3

*/