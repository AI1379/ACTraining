#include <bits/stdc++.h>
using namespace std;
#define ll long long
const ll MAXN = 127;
ll t;
ll n, k;
ll val[MAXN];
ll table[MAXN];
void solve() {
  memset(table, 0, sizeof(table));
  cin >> n >> k;
  for (int i = 1; i <= n; ++i) {
    cin >> val[i];
    val[i] = val[i] % k;
    table[val[i]]++;
  }
  for (int i = 1; i <= n; ++i) {
    if (table[val[i]] == 1) {
      cout << "YES\n" << i << endl;
      return;
    }
  }
  cout << "NO\n";
  return;
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


7
3 2
1 2 3
4 2
1 2 4 5
5 3
10 7 3 4 5
5 3
1 31 15 55 36
2 1
17 17
2 2
17 18
1 3
6

YES
2
NO
YES
3
NO
NO
YES
2
YES
1


*/