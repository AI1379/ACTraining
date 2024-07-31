#include <bits/stdc++.h>
#include <random>
using namespace std;
#define ll long long
#define ull unsigned long long
const ll MAXN = 1000010;
ll n;
ull rdmp[MAXN], xr[MAXN], val[MAXN], uniq[MAXN], tn;
ull ans;
int pos[MAXN][7], curl;
namespace PersSegt {
struct Node {
  ll lchild, rchild, val;
  ll l, r;
};
Node segt[MAXN << 5];
ll roots[MAXN];
ll tot;
ll build(ll l, ll r) {
  ll pos = ++tot;
  segt[pos].l = l;
  segt[pos].r = r;
  if (l == r) {
    segt[pos].val = 0;
    return pos;
  }
  ll mid = (l + r) / 2;
  segt[pos].lchild = build(l, mid);
  segt[pos].rchild = build(mid + 1, r);
  return pos;
}
ll query(ll p, ll cur) {
  if (segt[cur].l == p && segt[cur].r == p) {
    return segt[cur].val;
  }
  ll mid = (segt[cur].l + segt[cur].r) / 2;
  if (p <= mid) {
    return query(p, segt[cur].lchild);
  } else {
    return query(p, segt[cur].rchild);
  }
}
void modify(ll p, ll pre, ll cur) {
  segt[cur].l = segt[pre].l;
  segt[cur].r = segt[pre].r;
  if (segt[cur].l == p && segt[cur].r == p) {
    segt[cur].val = segt[pre].val + 1;
    return;
  }
  ll mid = (segt[cur].l + segt[cur].r) / 2;
  if (p <= mid) {
    segt[cur].lchild = ++tot;
    segt[cur].rchild = segt[pre].rchild;
    modify(p, segt[pre].lchild, segt[cur].lchild);
  } else {
    segt[cur].rchild = ++tot;
    segt[cur].lchild = segt[pre].lchild;
    modify(p, segt[pre].rchild, segt[cur].rchild);
  }
}
} // namespace PersSegt
int main() {
  std::random_device randiv;
  std::mt19937_64 rng(randiv());
  std::uniform_int_distribution<ull> dist;
  ios::sync_with_stdio(false);
  cin >> n;
  for (int i = 1; i <= n; ++i) {
    cin >> val[i];
    if (rdmp[val[i]] == 0)
      rdmp[val[i]] = dist(rng);
    xr[i] = xr[i - 1] ^ rdmp[val[i]];
    uniq[i] = xr[i];
  }
  // for (int i = 1; i <= n; ++i) {
  //   cout << xr[i] << ' ' << rdmp[val[i]] << ' ' << val[i] << endl;
  // }
  sort(uniq + 1, uniq + n + 1);
  tn = unique(uniq + 1, uniq + n + 1) - uniq - 1;
  using PersSegt::roots;
  using PersSegt::tot;
  roots[0] = PersSegt::build(1, tn);
  for (int i = 1; i <= n; ++i) {
    xr[i] = lower_bound(uniq + 1, uniq + tn + 1, xr[i]) - uniq;
    roots[i] = ++tot;
    PersSegt::modify(xr[i], roots[i - 1], roots[i]);
    // cout << xr[i] << ' ';
  }
  // cout << endl;
  for (int i = 1; i <= n; ++i) {
    pos[val[i]][3] = pos[val[i]][2];
    pos[val[i]][2] = pos[val[i]][1];
    pos[val[i]][1] = i;
    curl = max(curl, pos[val[i]][3]);
    ans += (PersSegt::query(xr[i], roots[i - 1]) -
            PersSegt::query(xr[i], roots[max(0, curl - 1)]));
    // cout << i << ' ' << curl << ' ' << ans << endl;
  }
  cout << ans << endl;
  return 0;
}
/**
5 3 5 5 4 4 3
*/