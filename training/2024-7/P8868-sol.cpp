#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define lson (cur * 2)
#define rson (cur * 2 + 1)
#define pll pair<ll, ll>
#define ull unsigned long long
const ll MAXN = 250010;
const ll MAXM = 250010;
struct info {
  ull s, sx, sy, sxy;
  info() { s = sx = sy = sxy = 0; }
  info(ull S, ull SX, ull SY, ull SXY) { s = S, sx = SX, sy = SY, sxy = SXY; }
  inline void clr() { s = sx = sy = sxy = 0; }
  inline void output() { printf("%llu %llu %llu %llu\n", s, sx, sy, sxy); }
} inf[MAXN << 2];
struct tag {
  ull cx, cy, ax, ay, axy, c;
  // tag() { cx = cy = ax = ay = axy = c = 0; }
  // tag(ull CX, ull CY, ull AX, ull AY, ull AXY, ull C) {
  // cx = CX, cy = CY, ax = AX, ay = AY, axy = AXY, c = C;
  // }
  inline void clr() { cx = cy = ax = ay = axy = c = 0; }
  inline bool empty() { return !(cx || cy || ax || ay || axy || c); }
  inline void output() {
    printf("%llu %llu %llu %llu %llu %llu\n", cx, cy, ax, ay, axy, c);
  }
} tg[MAXN << 2];
inline info merge(info x, info y) {
  return info(x.s + y.s, x.sx + y.sx, x.sy + y.sy, x.sxy + y.sxy);
}
inline tag merge(tag x, tag y) // x -> y
{
  if (y.cx && y.cy)
    y.c += x.axy * y.cx * y.cy + x.ax * y.cx + x.ay * y.cy + x.c;
  else if (y.cx) {
    y.ay += x.axy * y.cx + x.ay;
    y.c += x.c + x.ax * y.cx;
  } else if (y.cy) {
    y.ax += x.axy * y.cy + x.ax;
    y.c += x.c + x.ay * y.cy;
  } else {
    y.axy += x.axy;
    y.ax += x.ax;
    y.ay += x.ay;
    y.c += x.c;
  }
  if (x.cx)
    y.cx = x.cx;
  if (x.cy)
    y.cy = x.cy;
  return y;
}
inline info merge(info x, tag y, int len) {
  x.s += y.axy * x.sxy + y.ax * x.sx + y.ay * x.sy + y.c * len;
  if (y.cx && y.cy) {
    x.sxy = len * y.cx * y.cy;
    x.sx = len * y.cx;
    x.sy = len * y.cy;
  } else if (y.cx) {
    x.sxy = x.sy * y.cx;
    x.sx = len * y.cx;
  } else if (y.cy) {
    x.sxy = x.sx * y.cy;
    x.sy = len * y.cy;
  }
  return x;
}
#define ls(p) (p << 1)
#define rs(p) (p << 1 | 1)
inline void push_up(int p) { inf[p] = merge(inf[ls(p)], inf[rs(p)]); }
inline void push_down(int p, int l, int r) {
  if (!tg[p].empty()) {
    int mid = (l + r) >> 1;
    int l1 = (mid - l + 1), l2 = (r - mid);
    tg[ls(p)] = merge(tg[p], tg[ls(p)]), tg[rs(p)] = merge(tg[p], tg[rs(p)]);
    inf[ls(p)] = merge(inf[ls(p)], tg[p], l1),
    inf[rs(p)] = merge(inf[rs(p)], tg[p], l2);
    tg[p].clr();
    return;
  }
}
void update(int p, int l, int r, int nl, int nr, tag t) {
  if (nl <= l && nr >= r) {
    tg[p] = merge(t, tg[p]);
    inf[p] = merge(inf[p], t, r - l + 1);
    return;
  }
  push_down(p, l, r);
  int mid = (l + r) >> 1;
  if (nl <= mid)
    update(ls(p), l, mid, nl, nr, t);
  if (nr > mid)
    update(rs(p), mid + 1, r, nl, nr, t);
  push_up(p);
}
ull query(int p, int l, int r, int nl, int nr) {
  if (nl <= l && nr >= r) {
    return inf[p].s;
  }
  push_down(p, l, r);
  int mid = (l + r) >> 1;
  ull res = 0;
  if (nl <= mid)
    res += query(ls(p), l, mid, nl, nr);
  if (nr > mid)
    res += query(rs(p), mid + 1, r, nl, nr);
  push_up(p);
  return res;
}
ll n, t;
ull a[MAXN], b[MAXN];
ll q;
struct Query {
  ll idx, l, r;
  ull ans;
};
Query qs[MAXM];
ll stka[MAXN], topa;
ll stkb[MAXN], topb;
int main() {
  ios::sync_with_stdio(false);
  cin >> t >> n;
  for (int i = 1; i <= n; ++i) {
    cin >> a[i];
  }
  for (int i = 1; i <= n; ++i) {
    cin >> b[i];
  }
  cin >> q;
  // cout << q << endl;
  for (int i = 1; i <= q; ++i) {
    cin >> qs[i].l >> qs[i].r;
    qs[i].idx = i;
  }
  // cout << q << endl;
  sort(qs + 1, qs + q + 1,
       [](Query x, Query y) { return x.r == y.r ? x.l < y.l : x.r < y.r; });
  for (int i = 1, idx = 1; i <= n; ++i) {
    while (topa && a[stka[topa]] < a[i])
      --topa;
    update(1, 1, n, stka[topa] + 1, i, tag{.cx = a[i]});
    while (topb && b[stkb[topb]] < b[i])
      --topb;
    update(1, 1, n, stkb[topb] + 1, i, tag{.cy = b[i]});
    stka[++topa] = stkb[++topb] = i;
    update(1, 1, n, 1, i, tag{.axy = 1});
    while (qs[idx].r == i && idx <= q) {
      qs[idx].ans = query(1, 1, n, qs[idx].l, i);
      ++idx;
    }
  }
  sort(qs + 1, qs + q + 1, [](Query a, Query b) { return a.idx < b.idx; });
  for (int i = 1; i <= q; ++i) {
    cout << qs[i].ans << endl;
  }
  return 0;
}