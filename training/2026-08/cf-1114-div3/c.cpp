#include <bits/stdc++.h>
using namespace std;

#ifdef DEBUG
#define DOUT cerr
#else
#define DOUT                                                                   \
  if constexpr (false)                                                         \
  cerr
#endif

#define ll long long
#define ull unsigned long long

void solve(bool is_c1 = false) {
  ull n;
  string s, t;
  cin >> n >> s >> t;
  vector<ll> a[2], b[2];
  for (auto i = 0ull; i < n; ++i) {
    if (s[i] == '1')
      a[i % 2].push_back(i);
    if (t[i] == '1')
      b[i % 2].push_back(i);
  }
  if (a[0].size() != b[0].size() || a[1].size() != b[1].size()) {
    if (is_c1) {
      cout << "NO\n";
    } else {
      cout << "-1\n";
    }
    return;
  } else if (is_c1) {
    cout << "YES\n";
    return;
  }
  ll ans = 0;
  for (auto i = 0ull; i < 2; ++i) {
    for (auto j = 0ull; j < a[i].size(); ++j) {
      ans += abs(a[i][j] - b[i][j]);
    }
  }
  ans /= 2;
  cout << ans << "\n";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int t;
  cin >> t;
  while (t--) {
    solve(true);
  }
  return 0;
}