#include <bits/stdc++.h>
using namespace std;

#ifdef DEBUG
#define DOUT cerr
#else
#define DOUT \
  if constexpr (false) cerr
#endif

#define ll long long

void solve() {
  ll n, a, b;
  cin >> n >> a >> b;
  if (n % 2 == 1) {
    cout << "No\n";
    return;
  }
  bool black = (a + b) % 2 == 1;
  if (black) {
    cout << "No\n";
    return;
  }
  cout << "Yes\n";
  if (b == 1) {
  } else {

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