#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define ull unsigned long long
const ll MAXN = 250010;
const ll MAXM = 250010;
#define lson (cur * 2)
#define rson (cur * 2 + 1)
#define sgmid (segt[cur].mid)
namespace SegmentTree {
struct Info {
  ull s, sx, sy, sxy;
  ull len;
};
struct Tag {
  ull cx, cy;
  ull mx, my, mxy, mlen;
};
bool emptytag(const Tag &t) {
  return !(t.cx || t.cy || t.mx || t.my || t.mxy || t.mlen);
}
struct Node {
  ll l, r, mid;
  Info info;
  Tag tag;
};
Node segt[MAXN * 4];
ull a[MAXN], b[MAXN];
Info merge(const Info &lhs, const Info &rhs) {
  return {lhs.s + rhs.s, lhs.sx + rhs.sx, lhs.sy + rhs.sy, lhs.sxy + rhs.sxy,
          lhs.len + rhs.len};
}
Tag merge(const Tag &lhs, const Tag &rhs) {
  Tag res = lhs;
  if (lhs.cx && lhs.cy) {
    res.mlen += rhs.mxy * lhs.cx * lhs.cy + rhs.mx * lhs.cx + rhs.my * lhs.cy +
                rhs.mlen;
  } else if (lhs.cx) {
    res.my += rhs.mxy * lhs.cx + rhs.my;
    res.mlen += rhs.mlen + lhs.cx * rhs.mx;
  } else if (lhs.cy) {
    res.mx += rhs.mxy * lhs.cy + rhs.mx;
    res.mlen += rhs.mlen + lhs.cy * rhs.my;
  } else {
    res.mlen += rhs.mlen;
    res.mx += rhs.mx;
    res.my += rhs.my;
    res.mxy += rhs.mxy;
  }
  if (rhs.cx)
    res.cx = rhs.cx;
  if (rhs.cy)
    res.cy = rhs.cy;
  return res;
}
Info merge(const Info &val, const Tag &tag) {
  Info res = val;
  res.s += tag.mx * val.sx + tag.my * val.sy + tag.mxy * val.sxy +
           tag.mlen * val.len;
  if (tag.cx && tag.cy) {
    res.sxy = val.len * tag.cx * tag.cy;
    res.sx = val.len * tag.cx;
    res.sy = val.len * tag.cy;
  } else if (tag.cx) {
    res.sxy = tag.cx * val.sy;
    res.sx = tag.cx * val.len;
  } else if (tag.cy) {
    res.sxy = tag.cy * val.sx;
    res.sy = tag.cy * val.len;
  }
  return res;
}
void pushup(ll cur) {
  segt[cur].info = merge(segt[lson].info, segt[rson].info);
}
void pushdown(ll cur) {
  if (!emptytag(segt[cur].tag)) {
    segt[lson].tag = merge(segt[lson].tag, segt[cur].tag);
    segt[rson].tag = merge(segt[rson].tag, segt[cur].tag);
    segt[lson].info = merge(segt[lson].info, segt[cur].tag);
    segt[rson].info = merge(segt[rson].info, segt[cur].tag);
    segt[cur].tag = Tag{};
  }
}
void build(ll cur, ll l, ll r) {
  segt[cur].l = l;
  segt[cur].r = r;
  segt[cur].mid = (l + r) / 2;
  if (l == r) {
    segt[cur].info.len = 1;
    return;
  }
  build(lson, l, sgmid);
  build(rson, sgmid + 1, r);
  pushup(cur);
}
void update(ll cur, ll l, ll r, Tag t) {
  if (l <= segt[cur].l && segt[cur].r <= r) {
    segt[cur].info = merge(segt[cur].info, t);
    segt[cur].tag = merge(segt[cur].tag, t);
    return;
  }
  pushdown(cur);
  if (l <= sgmid)
    update(lson, l, r, t);
  if (sgmid + 1 <= r)
    update(rson, l, r, t);
  pushup(cur);
}
Info query(ll cur, ll l, ll r) {
  if (l <= segt[cur].l && segt[cur].r <= r) {
    return segt[cur].info;
  }
  Info res;
  pushdown(cur);
  if (l <= sgmid)
    res = merge(res, query(lson, l, r));
  if (sgmid + 1 <= r)
    res = merge(res, query(rson, l, r));
  return res;
}
} // namespace SegmentTree
struct Query {
  ll l, r, pos, ans;
};
ll n, q;
Query qs[MAXM];
ull lefta[MAXN], leftb[MAXN];
int stk1[MAXN], stk2[MAXN];
ll top1 = 0, top2 = 0;
int main() {
  using namespace SegmentTree;
  cin >> q >> n;
  for (int i = 1; i <= n; ++i) {
    cin >> a[i];
  }
  for (int i = 1; i <= n; ++i) {
    cin >> b[i];
  }
  SegmentTree::build(1, 1, n);
  cin >> q;
  for (int i = 1; i <= q; ++i) {
    cin >> qs[i].l >> qs[i].r;
    qs[i].pos = i;
  }
  sort(qs + 1, qs + q + 1,
       [](const Query &lhs, const Query &rhs) { return lhs.r < rhs.r; });
  for (int j = 1; j <= n; ++j) {
    while (top1 && a[stk1[top1]] < a[j])
      --top1;
    lefta[j] = stk1[top1] + 1;
    while (top2 && b[stk2[top2]] < b[j])
      --top2;
    leftb[j] = stk2[top2] + 1;
    stk1[++top1] = stk2[++top2] = j;
  }
  for (auto i = 1; i <= n; ++i) {
    cout << a[i] << ' ' << lefta[i] << ' ' << b[i] << ' ' << leftb[i] << endl;
  }
  for (int i = 1, j = 1; i <= n && j <= q; ++i) {
    update(1, lefta[i], i, Tag{a[i], 0, 0, 0, 0, 0});
    update(1, leftb[i], i, Tag{0, b[i], 0, 0, 0, 0});
    update(1, 1, i, Tag{0, 0, 0, 0, 1, 0});
    while (qs[j].r == i && j <= q) {
      qs[j].ans = query(1, qs[j].l, i).s;
      ++j;
    }
  }
  sort(qs + 1, qs + q + 1,
       [](const Query &lhs, const Query &rhs) { return lhs.pos < rhs.pos; });
  for (int i = 1; i <= q; ++i) {
    cout << qs[i].ans << endl;
  }
  return 0;
}