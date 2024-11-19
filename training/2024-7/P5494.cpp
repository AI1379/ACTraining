#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define lson(cur) (segt[cur].ls ? segt[cur].ls : segt[cur].ls = newnode())
#define rson(cur) (segt[cur].rs ? segt[cur].rs : segt[cur].rs = newnode())
#define pll pair<ll, ll>
const ll MAXN = 200010;
struct Node {
  ll ls, rs;
  ll val;
};
ll n, m;
ll tot;
Node segt[MAXN * 4];
ll roots[MAXN], cnt = 0;
ll gc[MAXN * 4], gcidx = 0;
ll newnode() { return gcidx ? gc[gcidx--] : ++tot; }
void delnode(ll pos) {
  segt[pos] = {0, 0, 0};
  gc[++gcidx] = pos;
}
void pushup(ll pos) {
  segt[pos].val = segt[segt[pos].ls].val + segt[segt[pos].rs].val;
}
void modify(ll cur, ll cl, ll cr, ll pos, ll delta) {
  if (cl == pos && cr == pos) {
    segt[cur].val += delta;
    return;
  }
  auto mid = (cl + cr) / 2;
  if (pos <= mid) {
    modify(lson(cur), cl, mid, pos, delta);
  } else {
    modify(rson(cur), mid + 1, cr, pos, delta);
  }
  pushup(cur);
}
ll merge(ll u, ll v, ll cl, ll cr) {
  if (u == 0 || v == 0)
    return u ^ v;
  if (cl == cr) {
    segt[u].val += segt[v].val;
    delnode(v);
    return u;
  }
  auto mid = (cl + cr) / 2;
  segt[u].ls = merge(segt[u].ls, segt[v].ls, cl, mid);
  segt[u].rs = merge(segt[u].rs, segt[v].rs, mid + 1, cr);
  pushup(u);
  delnode(v);
  return u;
}
void split(ll &u, ll &v, ll cl, ll cr, ll l, ll r) {
  if (!u || r < cl || l > cr)
    return;
  if (l <= cl && cr <= r) {
    v = u;
    u = 0;
    return;
  }
  if (!v)
    v = newnode();
  auto mid = (cl + cr) / 2;
  if (l <= mid)
    split(segt[u].ls, segt[v].ls, cl, m, l, r);
  if (mid + 1 <= r)
    split(segt[u].rs, segt[v].rs, mid + 1, cr, l, r);
  pushup(u);
  pushup(v);
}
ll querysum(ll cur, ll cl, ll cr, ll l, ll r) {
  if (cur == 0)
    return 0;
  if (l <= cl && cr <= r) {
    return segt[cur].val;
  }
  auto mid = (cl + cr) / 2;
  ll res = 0;
  if (l <= mid)
    res += querysum(segt[cur].ls, cl, mid, l, r);
  if (mid + 1 <= r)
    res += querysum(segt[cur].rs, mid + 1, cr, l, r);
  return res;
}
ll querykth(ll cur, ll cl, ll cr, ll rk) {
  if (segt[cur].val < rk)
    return -1;
  if (cl == cr)
    return cl;
  auto mid = (cl + cr) / 2;
  if (segt[segt[cur].ls].val >= rk)
    return querykth(segt[cur].ls, cl, mid, rk);
  else
    return querykth(segt[cur].rs, mid + 1, cr, rk - segt[segt[cur].ls].val);
}
int main() {
  ll op, u, v, w;
  cin >> n >> m;
  roots[++cnt] = newnode();
  for (int i = 1; i <= n; ++i) {
    cin >> u;
    if (u)
      modify(roots[cnt], 1, n, i, u);
  }
  for (int i = 1; i <= m; ++i) {
    cin >> op;
    if (op == 0) {
      cin >> w >> u >> v;
      split(w, roots[++cnt], 1, n, u, v);
    } else if (op == 1) {
      cin >> u >> v;
      roots[u] = merge(roots[u], roots[v], 1, n);
    } else if (op == 2) {
      cin >> u >> v >> w;
      cout << "modify" << endl;
      modify(roots[u], 1, n, w, v);
    } else if (op == 3) {
      cin >> w >> u >> v;
      cout << querysum(roots[w], 1, n, u, v) << endl;
    } else if (op == 4) {
      cin >> u >> v;
      cout << querykth(roots[u], 1, n, v) << endl;
    }
  }
  return 0;
}
/**
5 12
0 0 0 0 0
2 1 1 1
2 1 1 2
2 1 1 3
3 1 1 3
4 1 2
2 1 1 4
2 1 1 5
0 1 2 4
2 2 1 4
3 2 2 4
1 1 2
4 1 3
3
2
4
3
*/