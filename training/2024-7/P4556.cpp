#include <bits/stdc++.h>
using namespace std;
#define ll int
#define pll pair<ll, ll>
#define ls segt[cur].lson
#define rs segt[cur].rson
const ll MAXN = 100010;
struct Node {
  ll lson, rson;
  ll val, pos;
};
ll n, m;
Node segt[MAXN << 2];
ll tot;
ll roots[MAXN];
vector<ll> tree[MAXN];
vector<pll> qs[MAXN];
ll dep[MAXN], fa[MAXN], top[MAXN], siz[MAXN], prefer[MAXN], dfn[MAXN], curdfn;
ll ans[MAXN];
void getprefer(ll u) {
  siz[u] = 1;
  dep[u] = dep[fa[u]] + 1;
  for (auto v : tree[u]) {
    if (v == fa[u])
      continue;
    fa[v] = u;
    getprefer(v);
    siz[u] += siz[v];
    prefer[u] = siz[prefer[u]] < siz[v] ? v : prefer[u];
  }
}
void decompose(ll u, ll t) {
  dfn[u] = ++curdfn;
  top[u] = t;
  if (prefer[u])
    decompose(prefer[u], t);
  for (auto v : tree[u]) {
    if (v == fa[u] || v == prefer[u])
      continue;
    decompose(v, v);
  }
}
void pushup(ll cur) {
  if (ls && rs) {
    segt[cur].val = max(segt[ls].val, segt[rs].val);
    segt[cur].pos =
        (segt[ls].val >= segt[rs].val ? segt[ls].pos : segt[rs].pos);
  } else if (ls) {
    segt[cur].val = segt[ls].val;
    segt[cur].pos = segt[ls].pos;
  } else if (rs) {
    segt[cur].val = segt[rs].val;
    segt[cur].pos = segt[rs].pos;
  }
}
void modify(ll cur, ll cl, ll cr, ll pos, ll delta) {
  if (cl == pos && cr == pos) {
    segt[cur].val += delta;
    segt[cur].pos = pos;
    return;
  }
  auto mid = (cl + cr) / 2;
  if (pos <= mid) {
    if (!segt[cur].lson)
      segt[cur].lson = ++tot;
    modify(segt[cur].lson, cl, mid, pos, delta);
  } else {
    if (!segt[cur].rson)
      segt[cur].rson = ++tot;
    modify(segt[cur].rson, mid + 1, cr, pos, delta);
  }
  pushup(cur);
}
// ll merge(ll cur, ll pre, ll cl, ll cr) {
//   if (!cur)
//     return pre;
//   if (!pre)
//     return cur;
//   if (cl == cr) {
//     segt[cur].val += segt[pre].val;
//     return cur;
//   }
//   auto mid = (cl + cr) / 2;
//   ls = merge(ls, segt[pre].lson, cl, mid);
//   rs = merge(rs, segt[pre].rson, mid + 1, cr);
//   pushup(cur);
//   return cur;
// }
void addquery(ll u, ll v, ll w) {
  while (top[u] != top[v]) {
    if (dep[top[u]] < dep[top[v]])
      swap(u, v);
    qs[dfn[top[u]]].emplace_back(w, 1);
    qs[dfn[u] + 1].emplace_back(w, -1);
    u = fa[top[u]];
  }
  if (dfn[u] > dfn[v])
    swap(u, v);
  qs[dfn[u]].emplace_back(w, 1);
  qs[dfn[v] + 1].emplace_back(w, -1);
}
int main() {
  ll u, v, w, maxz = 0;
  cin >> n >> m;
  for (int i = 1; i <= n - 1; ++i) {
    cin >> u >> v;
    tree[u].emplace_back(v);
    tree[v].emplace_back(u);
    // roots[i] = ++tot;
  }
  // roots[n] = ++tot;
  getprefer(1);
  decompose(1, 1);
  for (int i = 1; i <= m; ++i) {
    cin >> u >> v >> w;
    addquery(u, v, w);
    maxz = max(maxz, w);
  }
  auto root = ++tot;
  for (int i = 1; i <= n; ++i) {
    // for (auto q : qs[i])
    // modify(roots[i], 1, n, q.first, q.second);
    // merge(roots[i], roots[i - 1], 1, n);
    // ans[i] = segt[roots[i]].val ? segt[roots[i]].pos : 0;
    for (auto q : qs[i])
      modify(root, 1, maxz, q.first, q.second);
    ans[i] = segt[root].val ? segt[root].pos : 0;
  }
  for (int i = 1; i <= n; ++i)
    cout << ans[dfn[i]] << endl;
  return 0;
}