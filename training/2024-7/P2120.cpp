#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define lson (cur * 2)
#define rson (cur * 2 + 1)
const ll MAXN = 1000010;
ll n;
ll s[MAXN], p[MAXN], c[MAXN];
ll sump[MAXN], sumpx[MAXN];
ll dp[MAXN];
ll k[MAXN], b[MAXN];
ll segt[MAXN * 4];
ll calc(ll id, ll x) { return k[id] * s[x] + b[id]; }
void update(ll cur, ll cl, ll cr, ll id) {
  if (cl == cr) {
    if (calc(id, cl) < calc(segt[cur], cl))
      segt[cur] = id;
    return;
  }
  auto mid = (cl + cr) / 2;
  if (calc(id, mid) < calc(segt[cur], mid))
    swap(id, segt[cur]);
  if (calc(id, cl) < calc(segt[cur], cl))
    update(lson, cl, mid, id);
  if (calc(id, cr) < calc(segt[cur], cr))
    update(rson, mid + 1, cr, id);
}
ll query(ll cur, ll cl, ll cr, ll x) {
  if (cl == cr) {
    return calc(segt[cur], x);
  }
  auto mid = (cl + cr) / 2;
  if (x <= mid)
    return min(calc(segt[cur], x), query(lson, cl, mid, x));
  else
    return min(calc(segt[cur], x), query(rson, mid + 1, cr, x));
}
int main() {
  ios::sync_with_stdio(false);
  cin >> n;
  for (int i = 1; i <= n; ++i) {
    cin >> s[i] >> p[i] >> c[i];
    sump[i] = sump[i - 1] + p[i];
    sumpx[i] = sumpx[i - 1] + p[i] * s[i];
  }
  b[0] = 1e17;
  for (int i = 1; i <= n; ++i) {
    dp[i] = min(0ll, query(1, 1, n, i)) + c[i] - sumpx[i] + sump[i] * s[i];
    k[i] = -sump[i];
    b[i] = dp[i] + sumpx[i];
    update(1, 1, n, i);
  }
  ll ans = dp[n];
  while (p[n--] == 0) {
    ans = min(ans, dp[n]);
  }
  cout << ans << endl;
  return 0;
}