#include <bits/stdc++.h>
using namespace std;
#define ll long long
const ll MAXN = 500010;
constexpr const ll INF = (1ll << 60);
constexpr const ll EMPTY_ASSIGN = -INF;
struct Node {
  ll l, r;
  struct Value {
    ll sum, rgmax, hismax, rgmin, len;
  } value;
  struct Tag {
    ll add, assign, maxadd;
  } tag;
  static constexpr const Tag EmptyTag = {0, EMPTY_ASSIGN, 0};
};
ll n, m;
ll a[MAXN];
Node segt[MAXN * 4];
#define lson (cur * 2)
#define rson (cur * 2 + 1)
Node::Value merge(Node::Value a, Node::Value b) {
  return {a.sum + b.sum, max(a.rgmax, b.rgmax), max(a.hismax, b.hismax),
          min(a.rgmin, b.rgmin), a.len + b.len};
}
Node::Value merge(Node::Value val, Node::Tag tag) {
  val.sum += tag.add * val.len;
  val.rgmax += tag.add;
  val.rgmin += tag.add;
  val.hismax += tag.maxadd;
  if (tag.assign != EMPTY_ASSIGN) {
    val.rgmax = val.rgmin = tag.assign;
    val.sum = tag.assign * val.len;
    val.hismax = max(val.hismax, tag.assign);
  }
  return val;
}
Node::Tag merge(Node::Tag a, Node::Tag b) {
  a.add += b.add;
  a.maxadd = max(a.maxadd, a.add);
  a.assign = b.assign;
  return a;
}
void pushup(ll cur) {
  segt[cur].value = merge(segt[lson].value, segt[rson].value);
}
void pushdown(ll cur) {
  segt[lson].value = merge(segt[lson].value, segt[cur].tag);
  segt[rson].value = merge(segt[rson].value, segt[cur].tag);
  segt[lson].tag = merge(segt[lson].tag, segt[cur].tag);
  segt[rson].tag = merge(segt[rson].tag, segt[cur].tag);
  segt[cur].tag = Node::EmptyTag;
}
void build(ll cur, ll l, ll r) {
  segt[cur].l = l;
  segt[cur].r = r;
  segt[cur].tag = Node::EmptyTag;
  auto mid = (l + r) / 2;
  if (l == r) {
    segt[cur].value.rgmin = segt[cur].value.rgmax = segt[cur].value.hismax =
        segt[cur].value.sum = a[l];
    segt[cur].value.len = 1;
    return;
  }
  build(lson, l, mid);
  build(rson, mid + 1, r);
  pushup(cur);
}
Node::Value query(ll cur, ll l, ll r) {
  if (l <= segt[cur].l && segt[cur].r <= r) {
    return segt[cur].value;
  }
  auto mid = (segt[cur].l + segt[cur].r) / 2;
  Node::Value res{};
  pushdown(cur);
  if (l <= mid)
    res = merge(res, query(lson, l, r));
  if (mid + 1 <= r)
    res = merge(res, query(rson, l, r));
  return res;
}
void modify(ll cur, ll l, ll r, Node::Tag tag) {
  if (l <= segt[cur].l && segt[cur].r <= r &&
      segt[cur].value.rgmin >= tag.assign) {
    segt[cur].value = merge(segt[cur].value, tag);
    segt[cur].tag = merge(segt[cur].tag, tag);
    return;
  } else if (tag.assign > segt[cur].value.rgmax) {
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
int main() {
  ll op, l, r, k;
  ios::sync_with_stdio(false);
  cin >> n >> m;
  for (int i = 1; i <= n; ++i)
    cin >> a[i];
  build(1, 1, n);
  while (m--) {
    cin >> op;
    if (op == 1) {
      cin >> l >> r >> k;
      modify(1, l, r, Node::Tag{k, EMPTY_ASSIGN, 0});
    } else if (op == 2) {
      cin >> l >> r >> k;
      modify(1, l, r, Node::Tag{0, k, 0});
    } else if (op == 3) {
      cin >> l >> r;
      cout << query(1, l, r).sum << endl;
    } else if (op == 4) {
      cin >> l >> r;
      cout << query(1, l, r).rgmax << endl;
    } else if (op == 5) {
      cin >> l >> r;
      cout << query(1, l, r).hismax << endl;
    }
  }
  return 0;
}