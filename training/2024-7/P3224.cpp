#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pll pair<ll, ll>
#define ls segt[cur].lson
#define rs segt[cur].rson
const ll MAXN = 100010;
struct Node {
  ll lson, rson;
  ll val, pos;
};
ll n, m;
ll tot;
Node segt[MAXN * 40];
ll fa[MAXN];
ll roots[MAXN];
ll find(ll p) { return fa[p] == p ? p : fa[p] = find(fa[p]); }
void pushup(ll cur) { segt[cur].val = segt[ls].val + segt[rs].val; }
void modify(ll cur, ll cl, ll cr, ll pos, ll k) {
  if (cl == pos && cr == pos) {
    ++segt[cl].val;
    segt[cl].pos = k;
    return;
  }
  auto mid = (cl + cr) / 2;
  if (pos <= mid)
    modify(ls ? ls : ls = ++tot, cl, mid, pos, k);
  else
    modify(rs ? rs : rs = ++tot, mid + 1, cr, pos, k);
  pushup(cur);
}
ll merge(ll cur, ll pre, ll cl, ll cr) {
  if (cur == 0 || pre == 0)
    return cur ^ pre;
  auto mid = (cl + cr) / 2;
  ls = merge(ls, segt[pre].lson, cl, mid);
  rs = merge(rs, segt[pre].rson, mid + 1, cr);
  return cur;
}
ll query(ll cur, ll cl, ll cr, ll k) {
  if (cur == 0) {
    return -1;
  } else if (cl == cr) {
    return segt[cur].pos;
  }
  auto mid = (cl + cr) / 2;
  if (segt[ls].val >= k)
    return query(ls, cl, mid, k);
  else
    return query(rs, mid + 1, cr, k - segt[ls].val);
}
void merge(ll u, ll v) {
  auto fau = find(u), fav = find(v);
  if (fau == fav)
    return;
  roots[fau] = merge(roots[fau], roots[fav], 1, n);
  fa[fav] = fau;
}
int main() {
  char op;
  ll q, u, v;
  cin >> n >> m;
  for (int i = 1; i <= n; ++i) {
    cin >> u;
    fa[i] = i;
    roots[i] = ++tot;
    modify(roots[i], 1, n, u, i);
  }
  for (int i = 1; i <= m; ++i) {
    cin >> u >> v;
    merge(u, v);
  }
  cin >> q;
  while (q--) {
    cin >> op >> u >> v;
    if (op == 'Q')
      cout << query(roots[find(u)], 1, n, v) << endl;
    if (op == 'B')
      merge(u, v);
    for (int i = 1; i <= n; ++i) {
      cout << i << ' ' << roots[i] << ' ' << find(i) << endl;
    }
    cout << endl;
  }
  return 0;
}
/**
5 1
4 3 2 5 1
1 2
7
Q 3 2
Q 2 1
B 2 3
B 1 5
Q 2 1
Q 2 4
Q 2 3
*/