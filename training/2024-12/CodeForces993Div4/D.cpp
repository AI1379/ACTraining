#include <bits/stdc++.h>
using namespace std;
#define ll long long
const ll MAXN = 200010;
ll t;
ll n;
ll a[MAXN];
ll b[MAXN];
ll fst[MAXN];
void solve() {
  ll cur = 1;
  cin >> n;
  memset(fst, 0, sizeof(fst));
  for (int i = 1; i <= n; ++i) {
    cin >> a[i];
    if (!fst[a[i]]) {
      fst[a[i]] = i;
    }
  }
  for (int i = 1; i <= n; ++i) {
    if (i == fst[a[i]]) {
      b[i] = a[i];
    } else {
      while (fst[cur])
        ++cur;
      b[i] = cur;
      fst[cur] = i;
    }
  }
  for (int i = 1; i <= n; ++i) {
    cout << b[i] << ' ';
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
/*
4
2
1 2
4
1 1 1 2
8
4 5 5 5 1 1 2 1
10
1 1 2 2 1 1 3 3 1 1

1 2
1 1 2 2
4 5 5 1 1 2 2 3
1 8 2 2 1 3 3 9 1 1

*/