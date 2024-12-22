#include <bits/stdc++.h>
using namespace std;
#define ll long long
const ll MAXN = 100010;
ll t;
ll n, k;
ll ans[MAXN];
void solve() {
  ll cur = 1;
  memset(ans, 0, sizeof(ans));
  cin >> n >> k;
  for (int i = k; i <= n; i += k) {
    ans[i] = cur++;
  }
  for (int i = 1; i <= n; i++) {
    if (ans[i] == 0) {
      ans[i] = cur++;
    }
  }
  for (int i = 1; i <= n; i++) {
    cout << ans[i] << " ";
  }
  cout << endl;
}
int main() {
  ios::sync_with_stdio(false);
  cin >> t;
  while (t--) {
    solve();
  }
  return 0;
}