#include <bits/stdc++.h>
using namespace std;
#define ll long long
const ll MAXN = 127;
ll t;
ll n;
ll a[MAXN], b[MAXN];
ll ans = 0;
void solve() {
  ans = 0;
  cin >> n;
  for (int i = 1; i <= n; ++i)
    cin >> a[i];
  for (int i = 1; i <= n; ++i)
    cin >> b[i];
  a[n + 1] = b[n + 1] = 0;
  for (int i = 1; i <= n; ++i) {
    ans += max(0ll, a[i] - b[i + 1]);
  }
  cout << ans << endl;
}
int main() {
  ios::sync_with_stdio(false);
  cin >> t;
  while (t--) {
    solve();
  }
  return 0;
}
/*
4
2
3 2
2 1
1
5
8
3
1 1 1
2 2 2
6
8 2 5 6 2 6
8 2 7 4 3 4

4
5
1
16
*/