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

void solve() {
  int n;
  string s, t;
  cin >> n >> s;
  t = s;
  auto sz = unique(t.begin(), t.end()) - t.begin();
  bool flag_merge = false, flag_single = false;
  for (auto i = 1ull; i < s.length() - 1; ++i) {
    if (s[i] != s[i - 1] && s[i] != s[i + 1]) {
      if (s[i + 1] == s[i - 1]) {
        flag_merge = true;
      } else {
        flag_single = true;
      }
    }
  }
  if (flag_merge) {
    cout << sz - 2 << "\n";
  } else if (flag_single) {
    cout << sz - 1 << "\n";
  } else {
    cout << sz << "\n";
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int t;
  cin >> t;
  while (t--) {
    solve();
  }
  return 0;
}