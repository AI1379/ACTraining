#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pll pair<ll, ll>
const ll MAXN = 200010;
ll n, k;
ll a[MAXN], b[MAXN];
void solve() {
  cin >> n >> k;
  for (int i = 0; i < n; i++)
    cin >> a[i];
  for (int i = 0; i < n; i++)
    cin >> b[i];
  int s = -1;
  for (int i = 0; i < n; i++) {
    if (b[i] != -1) {
      if (s == -1)
        s = a[i] + b[i];
      else {
        if (s != a[i] + b[i]) {
          cout << 0 << '\n';
          return;
        }
      }
    }
  }
  if (s == -1) {
    int mx = *max_element(a, a + n) - *min_element(a, a + n);
    cout << k - mx + 1 << '\n';
    return;
  }
  for (int i = 0; i < n; i++) {
    if (a[i] > s || s - a[i] > k) {
      cout << 0 << '\n';
      return;
    }
  }
  cout << 1 << '\n';
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