#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pll pair<ll, ll>
const ll MAXN = 100010;
int n;
int val[MAXN];
int tail[MAXN], cur;
int main() {
  ios::sync_with_stdio(false);
  cin >> n;
  for (int i = 1; i <= n; ++i) {
    cin >> val[i];
  }
  tail[++cur] = val[1];
  for (int i = 2; i <= n; ++i) {
    if (val[i] > tail[cur]) {
      tail[++cur] = val[i];
    } else {
      int p = lower_bound(tail + 1, tail + cur + 1, val[i]) - tail;
      tail[p] = val[i];
    }
  }
  cout << cur << endl;
  return 0;
}