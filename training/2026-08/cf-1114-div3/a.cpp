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
  int a[3];
  for (int i = 0; i < 3; i++) {
    cin >> a[i];
  }
  sort(a, a + 3);
  cout << min(a[2] - a[1], a[1] - a[0]) << "\n";
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