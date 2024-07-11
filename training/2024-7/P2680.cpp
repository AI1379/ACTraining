#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pll pair<ll, ll>
const ll MAXN = 300010;
const ll MAXM = 300010;
ll n, m;
vector<ll> tree[MAXN];
struct {
  ll a, b, t;
} edges[MAXN];
ll val[MAXN];
ll dep[MAXN], prefer[MAXN], siz[MAXN], fa[MAXN];
ll top[MAXN], dfn[MAXN], node[MAXN];
#define lson (cur * 2)
#define rson (cur * 2 + 1)
#define sgmid (segt[cur].mid)
struct Node {
  ll l, r, mid;
  struct Info {
    ll inmx, exmx, val, ans;
    // inmx: max weight of all route including edge in the range of this node
    // exmx: max weight of all route excluding edge in the range of this node
    // val: value of an edge in leaf nodes
    // ans: min res of all leave nodes in the range
    // ans = max(inmx - val, exmx) for all leaves
    // Segment Tree Beats
    // ans = min_i=l^r(max(inmx_i-val_i, exmx_i))
  } val;
  struct Tag {
    ll inmx, exmx;
    // inmx: tag of Info::inmx
    // exmx: tag of Info::exmx
  } tag;
};
pll qs[MAXM];
ll len[MAXM];
Node segt[MAXN * 4];
Node::Info merge(Node::Info lhs, Node::Info rhs) {
  return Node::Info{max(lhs.inmx, rhs.inmx), max(lhs.exmx, rhs.exmx),
                    lhs.val + rhs.val, min(lhs.ans, rhs.ans)};
}
Node::Tag merge(Node::Tag lhs, Node::Tag rhs) {
  return Node::Tag{max(lhs.inmx, rhs.inmx), max(lhs.exmx, rhs.exmx)};
}
Node::Info merge(Node::Info info, Node::Tag tag) { return info; }
void pushup(ll cur) { segt[cur].val = merge(segt[lson].val, segt[rson].val); }
void pushdown(ll cur) {
  segt[lson].val = merge(segt[lson].val, segt[cur].tag);
  segt[rson].val = merge(segt[rson].val, segt[cur].tag);
  segt[lson].tag = merge(segt[cur].tag, segt[lson].tag);
  segt[rson].tag = merge(segt[cur].tag, segt[rson].tag);
}
void build(ll cur, ll l, ll r) {
  segt[cur].l = l;
  segt[cur].r = r;
  segt[cur].mid = (l + r) / 2;
  if (l == r) {
    segt[cur].val = Node::Info{0, 0, val[l], 0};
    return;
  }
  build(lson, l, sgmid);
  build(rson, sgmid + 1, r);
  pushup(cur);
}
void modify(ll cur, ll l, ll r, Node::Tag t) {
  if (l > r)
    swap(l, r);
  if (l <= segt[cur].l && segt[cur].r <= r) {
    merge(segt[cur].val, t);
    merge(t, segt[cur].tag);
    return;
  }
  pushdown(cur);
  if (l <= sgmid)
    modify(lson, l, r, t);
  if (sgmid + 1 <= r)
    modify(rson, l, r, t);
  pushup(cur);
}
Node::Info query(ll cur, ll l, ll r) {
  if (l > r)
    swap(l, r);
  if (l <= segt[cur].l && segt[cur].r <= r) {
    return segt[cur].val;
  }
  pushdown(cur);
  auto res = Node::Info{};
  if (l <= sgmid)
    res = merge(res, query(lson, l, r));
  if (sgmid + 1 <= r)
    res = merge(res, query(rson, l, r));
  return res;
}
void getprefer(ll u) {
  siz[u] = 1;
  dep[u] = dep[fa[u]] + 1;
  for (auto v : tree[u]) {
    if (v == fa[u])
      continue;
    fa[v] = u;
    getprefer(v);
    siz[u] += siz[v];
    prefer[u] = siz[prefer[u]] > siz[v] ? prefer[u] : v;
  }
}
void decompose(ll u, ll t) {
  static ll cur = 0;
  dfn[u] = ++cur;
  node[dfn[u]] = u;
  top[u] = t;
  decompose(prefer[u], t);
  for (auto v : tree[u]) {
    if (v == fa[u] || v == prefer[u])
      continue;
    decompose(v, v);
  }
}
int main() {
  ll a, b, t;
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> n >> m;
  for (int i = 1; i <= n - 1; ++i) {
    cin >> edges[i].a >> edges[i].b >> edges[i].t;
    tree[a].emplace_back(b);
    tree[b].emplace_back(a);
  }
  getprefer(1);
  decompose(1, 1);
  for (int i = 1; i <= n - 1; ++i) {
    if (dep[edges[i].a] > dep[edges[i].b])
      val[dfn[edges[i].a]] = edges[i].t;
    else
      val[dfn[edges[i].b]] = edges[i].t;
  }
  build(1, 1, n);
  for (int i = 1; i <= m; ++i) {
    cin >> qs[i].first >> qs[i].second;
  }
  priority_queue<ll, vector<ll>, greater<ll>> heap;
  for (int i = 1; i <= m; ++i) {
    auto u = qs[i].first, v = qs[i].second;
    while (top[u] != top[v]) {
      if (dep[top[u]] < dep[top[v]])
        swap(u, v);
      len[i] += query(1, dfn[top[u]], dfn[u]).val;
      u = fa[top[u]];
    }
    len[i] += query(1, dfn[u], dfn[v]).val;
    len[i] -= val[min(dfn[u], dfn[v])];
  }
  for (int i = 1; i <= m; ++i) {
    auto u = qs[i].first, v = qs[i].second;
    while (top[u] != top[v]) {
      if (dep[top[u]] < dep[top[v]])
        swap(u, v);
      modify(1, dfn[top[u]], dfn[u], Node::Tag{len[i], 0});
      heap.push(dfn[top[u]]);
      heap.push(dfn[u]);
      u = fa[top[u]];
    }
    if (dfn[u] > dfn[v])
      swap(u, v);
    if (dfn[u] != dfn[v]) {
      modify(1, dfn[u] + 1, dfn[v], Node::Tag{len[i], 0});
      heap.push(dfn[u] + 1);
      heap.push(dfn[v]);
    }
    ll cur = 1, t;
    while (!heap.empty()) {
      t = heap.top();
      heap.pop();
      if (cur <= t - 1)
        modify(1, cur, t - 1, Node::Tag{0, len[i]});
      cur = heap.top() + 1;
      heap.pop();
    }
    if (cur < n)
      modify(1, cur, n, Node::Tag{0, len[i]});
  }
  cout << segt[1].val.ans << endl;
  return 0;
}