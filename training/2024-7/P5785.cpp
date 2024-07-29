#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define lson (cur * 2)
#define rson (cur * 2 + 1)
const ll MAXN = 300010;
ll n, s;
ll t[MAXN], c[MAXN];
ll sumt[MAXN], sumc[MAXN];
ll k[MAXN], b[MAXN];
ll unisumt[MAXN], pos[MAXN], tn;
ll segt[MAXN * 4];
ll dp[MAXN];
ll calc(ll id, ll x) { return k[id] * unisumt[x] + b[id]; }
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
  else if (calc(id, cr) < calc(segt[cur], cr))
    update(rson, mid + 1, cr, id);
}
ll query(ll cur, ll cl, ll cr, ll x) {
  if (cl == cr)
    return calc(segt[cur], x);
  auto mid = (cl + cr) / 2;
  if (x <= mid)
    return min(calc(segt[cur], x), query(lson, cl, mid, x));
  else
    return min(calc(segt[cur], x), query(rson, mid + 1, cr, x));
  return 0;
}
int main() {
  cin >> n >> s;
  tn = n;
  for (int i = 1; i <= n; ++i) {
    cin >> t[i] >> c[i];
    unisumt[i] = sumt[i] = sumt[i - 1] + t[i];
    sumc[i] = sumc[i - 1] + c[i];
  }
  sort(unisumt + 1, unisumt + n + 1);
  tn = unique(unisumt + 1, unisumt + n + 1) - unisumt - 1;
  for (int i = 1; i <= n; ++i) {
    pos[i] = lower_bound(unisumt + 1, unisumt + tn + 1, sumt[i]) - unisumt;
  }
  b[0] = 1e18;
  for (int i = 1; i <= n; ++i) {
    dp[i] = min(s * sumc[n], query(1, 1, tn, pos[i])) + sumt[i] * sumc[i];
    k[i] = -sumc[i];
    b[i] = dp[i] + s * (sumc[n] - sumc[i]);
    update(1, 1, tn, i);
  }
  cout << dp[n] << endl;
  return 0;
}