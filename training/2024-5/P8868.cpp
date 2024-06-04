#include <bits/stdc++.h>
using namespace std;
#define ll long long
const ll MAXN = 250010;
const ll MAXM = 250010;
#define lson (cur * 2)
#define rson (cur * 2 + 1)
#define sgmid (segt[cur].mid)
namespace SegmentTree {
struct Info {
  ll s, sx, sy, sxy;
  ll len;
};
struct Tag {
  ll cx, cy;
  ll mx, my, mxy, mlen;
};
bool emptytag(const Tag &t) {
  return !(t.cx || t.cy || t.mx || t.my || t.mxy || t.mlen);
}
struct Node {
  ll l, r, mid;
  Info info;
  Tag tag;
};
Node *segt;
ll *a, *b;
Info merge(const Info &lhs, const Info &rhs) {
  return {lhs.s + rhs.s, lhs.sx + rhs.sx, lhs.sy + rhs.sy, lhs.sxy + rhs.sxy,
          lhs.len + rhs.len};
}
Tag merge(const Tag &lhs, const Tag &rhs) {}
Info merge(const Info &val, const Tag &tag) {}
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
    segt[cur].info.sxy = segt[cur].info.s = a[l] * b[l];
    segt[cur].info.sx = a[l];
    segt[cur].info.sy = b[l];
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
SegmentTree::Node segt[MAXN * 4];
ll a[MAXN], b[MAXN];
Query qs[MAXM];
int main() {
  cin >> q >> n;
  for (int i = 1; i <= n; ++i) {
    cin >> a[i];
  }
  for (int i = 1; i <= n; ++i) {
    cin >> b[i];
  }
  SegmentTree::segt = segt;
  SegmentTree::a = a;
  SegmentTree::b = b;
  cin >> q;
  for (int i = 1; i <= q; ++i) {
    cin >> qs[i].l >> qs[i].r;
    qs[i].pos = i;
  }
  sort(qs + 1, qs + q + 1,
       [](const Query &lhs, const Query &rhs) { return lhs.r < rhs.r; });

  sort(qs + 1, qs + q + 1,
       [](const Query &lhs, const Query &rhs) { return lhs.pos < rhs.pos; });
  for (int i = 1; i <= q; ++i) {
    cout << qs[i].pos << endl;
  }
  return 0;
}