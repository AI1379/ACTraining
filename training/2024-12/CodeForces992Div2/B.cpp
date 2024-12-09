#include <bits/stdc++.h>
using namespace std;
#define ll long long
const ll MAXN = 100010;
ll n, c;
ll ans;
ll table[MAXN];
void init() {
  table[1] = 1;
  for (int i = 2; (1ll << i) <= MAXN; ++i) {
    table[i] = (table[i - 1] + 1) * 2;
    c = i;
  }
}
void solve() {
  ans = 0;
  cin >> n;
  ans = lower_bound(table, table + c + 1, n) - table;
  cout << ans << endl;
}
int main() {
  ll t;
  ios::sync_with_stdio(false);
  cin >> t;
  init();
  while (t--) {
    solve();
  }
  return 0;
}