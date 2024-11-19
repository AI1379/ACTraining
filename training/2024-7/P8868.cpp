#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define lson (cur * 2)
#define rson (cur * 2 + 1)
#define pll pair<ll, ll>
#define ull unsigned long long
const ll MAXN = 250010;
const ll MAXM = 250010;
struct Info {
  ull s, sxy, sx, sy, len;
};
struct Tag {
  ull cx, cy, mxy, mx, my, mlen;
};
struct Node {
  ll l, r;
  Info info;
  Tag tag;
};
bool notempty(Tag tag) {
  return tag.cx || tag.cy || tag.mlen || tag.mx || tag.mxy || tag.my;
}
Node segt[MAXN * 4];
Info merge(Info lhs, Info rhs) {
  return Info{.s = lhs.s + rhs.s,
              .sxy = lhs.sxy + rhs.sxy,
              .sx = lhs.sx + rhs.sx,
              .sy = lhs.sy + rhs.sy,
              .len = lhs.len + rhs.len};
}
Info merge(Info info, Tag tag) {
  info.s += tag.mxy * info.sxy + tag.mx * info.sx + tag.my * info.sy +
            tag.mlen * info.len;
  if (tag.cx && tag.cy) {
    info.sxy = tag.cx * tag.cy * info.len;
    info.sx = tag.cx * info.len;
    info.sy = tag.cy * info.len;
  } else if (tag.cx) {
    info.sxy = tag.cx * info.sy;
    info.sx = tag.cx * info.len;
  } else if (tag.cy) {
    info.sxy = tag.cy * info.sx;
    info.sy = tag.cy * info.len;
  }
  return info;
}
Tag merge(Tag pre, Tag cur) {
  if (pre.cx && pre.cy) {
    pre.mlen += cur.mxy * pre.cx * pre.cy + cur.mx * pre.cx + cur.my * pre.my +
                cur.mlen;
  } else if (pre.cx) {
    pre.my += cur.mxy * pre.cx + cur.my;
    pre.mlen += cur.mlen + cur.mx * pre.cx;
  } else if (pre.cy) {
    pre.mx += cur.mxy * pre.cy + cur.mx;
    pre.mlen += cur.mlen + cur.my * pre.cy;
  } else {
    pre.mlen += cur.mlen;
    pre.mx += cur.mx;
    pre.my += cur.my;
    pre.mxy += cur.mxy;
  }
  if (cur.cx)
    pre.cx = cur.cx;
  if (cur.cy)
    pre.cy = cur.cy;
  return pre;
}
void pushup(ll cur) {
  segt[cur].info = merge(segt[lson].info, segt[rson].info);
}
void pushdown(ll cur) {
  if (notempty(segt[cur].tag)) {
    segt[lson].tag = merge(segt[lson].tag, segt[cur].tag);
    segt[rson].tag = merge(segt[rson].tag, segt[cur].tag);
    segt[lson].info = merge(segt[lson].info, segt[cur].tag);
    segt[rson].info = merge(segt[rson].info, segt[cur].tag);
    segt[cur].tag = {0, 0, 0, 0, 0, 0};
  }
}
void build(ll cur, ll l, ll r) {
  segt[cur].l = l;
  segt[cur].r = r;
  // segt[cur].info.len = r - l + 1;
  if (l == r) {
    segt[cur].info.len = 1;
    return;
  }
  auto mid = (l + r) / 2;
  build(lson, l, mid);
  build(rson, mid + 1, r);
  pushup(cur);
}
Info query(ll cur, ll l, ll r) {
  if (l <= segt[cur].l && segt[cur].r <= r) {
    return segt[cur].info;
  }
  Info res{};
  auto mid = (segt[cur].l + segt[cur].r) / 2;
  assert(res.s == 0);
  pushdown(cur);
  if (l <= mid)
    res = merge(res, query(lson, l, r));
  if (mid + 1 <= r)
    res = merge(res, query(rson, l, r));
  return res;
}
void modify(ll cur, ll l, ll r, Tag tag) {
  assert(segt[cur].r - segt[cur].l + 1 == segt[cur].info.len);
  if (l <= segt[cur].l && segt[cur].r <= r) {
    segt[cur].info = merge(segt[cur].info, tag);
    segt[cur].tag = merge(segt[cur].tag, tag);
    return;
  }
  auto mid = (segt[cur].l + segt[cur].r) / 2;
  pushdown(cur);
  if (l <= mid)
    modify(lson, l, r, tag);
  if (mid + 1 <= r)
    modify(rson, l, r, tag);
  pushup(cur);
}
ll n, t;
ull a[MAXN], b[MAXN];
ll q;
struct Query {
  ll idx, l, r;
  ull ans;
};
Query qs[MAXM];
ll stka[MAXN], topa = 0;
ll stkb[MAXN], topb = 0;
int main() {
  ios::sync_with_stdio(false);
  cin >> t >> n;
  for (int i = 1; i <= n; ++i) {
    cin >> a[i];
  }
  for (int i = 1; i <= n; ++i) {
    cin >> b[i];
  }
  build(1, 1, n);
  cin >> q;
  for (int i = 1; i <= q; ++i) {
    cin >> qs[i].l >> qs[i].r;
    qs[i].idx = i;
  }
  sort(qs + 1, qs + q + 1,
       [](Query x, Query y) { return x.r == y.r ? x.l < y.l : x.r < y.r; });
  for (int i = 1, idx = 1; i <= n; ++i) {
    while (topa && a[stka[topa]] < a[i])
      --topa;
    modify(1, stka[topa] + 1, i, Tag{.cx = a[i]});
    while (topb && b[stkb[topb]] < b[i])
      --topb;
    modify(1, stkb[topb] + 1, i, Tag{.cy = b[i]});
    stka[++topa] = stkb[++topb] = i;
    modify(1, 1, i, Tag{.mxy = 1});
    while (qs[idx].r == i && idx <= q) {
      qs[idx].ans = query(1, qs[idx].l, i).s;
      ++idx;
    }
  }
  sort(qs + 1, qs + q + 1, [](Query a, Query b) { return a.idx < b.idx; });
  for (int i = 1; i <= q; ++i) {
    cout << qs[i].ans << endl;
  }
  return 0;
}