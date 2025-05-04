#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pll pair<ll, ll>
const ll INF = 1ll << 62;
void solve() {
  ll n, m;
  cin >> n >> m;
  vector<ll> a(n), b(m);
  for (ll i = 0; i < n; i++)
    cin >> a[i];
  for (ll i = 0; i < m; i++)
    cin >> b[i];
  vector<ll> backwards_match(m);
  ll j = n - 1;
  for (ll i = m - 1; i >= 0; i--) {
    while (j >= 0 && a[j] < b[i])
      j--;
    backwards_match[i] = j--;
  }
  vector<ll> forwards_match(m);
  j = 0;
  for (ll i = 0; i < m; i++) {
    while (j < n && a[j] < b[i])
      j++;
    forwards_match[i] = j++;
  }
  if (forwards_match.back() < n) {
    cout << 0 << endl;
    return;
  }
  ll ans = INF;
  for (ll i = 0; i < m; i++) {
    ll match_previous = i == 0 ? -1 : forwards_match[i - 1];
    ll match_next = i + 1 == m ? n : backwards_match[i + 1];
    if (match_next > match_previous) {
      ans = min(ans, b[i]);
    }
  }
  cout << (ans == INF ? -1 : ans) << "\n";
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