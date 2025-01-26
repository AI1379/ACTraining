#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pll pair<ll, ll>
const ll INF = 1ll << 62;
void solve() {
  ll n;
  cin >> n;
  vector<ll> a(n);
  for (auto &x : a) {
    cin >> x;
  }
  for (auto i = 0; i < n - 1; ++i) {
    if (a[i] > a[i + 1]) {
      cout << "NO\n";
      return;
    } else {
      a[i + 1] -= a[i];
      a[i] = 0;
    }
  }
  cout << "YES\n";
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
5
5
1 2 3 4 5
4
4 3 2 1
4
4 5 2 3
8
4 5 4 5 4 5 4 5
9
9 9 8 2 4 4 3 5 3

YES
NO
YES
YES
NO
*/