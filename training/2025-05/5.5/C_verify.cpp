#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pll pair<ll, ll>
const ll MAXN = 100010;
int n;
int val[MAXN], tmp[MAXN], tot;
int bit[MAXN];
int dp[MAXN];
int lowbit(int x) { return x & (-x); }
void add(int x, int v) {
  for (; x <= n; x += lowbit(x)) {
    bit[x] = max(bit[x], v);
  }
}
int sum(int x) {
  int ans = 0;
  for (; x; x -= lowbit(x)) {
    ans = max(ans, bit[x]);
  }
  return ans;
}
int main() {
  ios::sync_with_stdio(false);
  cin >> n;
  for (int i = 1; i <= n; ++i) {
    cin >> val[i];
    tmp[i] = val[i];
  }

  sort(tmp + 1, tmp + n + 1);
  tot = unique(tmp + 1, tmp + n + 1) - tmp - 1;
  for (int i = 1; i <= n; ++i) {
    val[i] = lower_bound(tmp + 1, tmp + tot + 1, val[i]) - tmp;
  }

  for (int i = 1; i <= n; ++i) {
    dp[i] = sum(val[i] - 1) + 1;
    add(val[i], dp[i]);
  }
  int ans = 0;
  for (int i = 1; i <= n; ++i) {
    ans = max(ans, dp[i]);
  }
  cout << ans << endl;
  return 0;
}