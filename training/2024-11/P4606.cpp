#include <bits/stdc++.h>
#include <iostream>
using namespace std;
#define ll long long
constexpr ll MAXN = 100010;
ll T;
ll n, m;
namespace Tarjan {
vector<ll> graph[MAXN];

ll dfn[MAXN], low[MAXN], idx = 0;
ll stk[MAXN], top = 0;
ll vbcccnt = 0;

void tarjan(ll u, ll fa);

} // namespace Tarjan

namespace Tree {

int n2;
int q;
vector<ll> tree[MAXN * 2];
ll dfn[MAXN * 2], idx = 0, node[MAXN * 2];
ll top[MAXN * 2], son[MAXN * 2], fa[MAXN * 2], dep[MAXN * 2], size[MAXN * 2];
ll pts[MAXN], s = 0;
ll ans = 0;

// use a segment tree to maintain the sum of the subtree
namespace SegTree {

ll sum[MAXN * 2 * 4], tag[MAXN * 2 * 4];
void pushup(int rt) { sum[rt] = sum[rt << 1] + sum[rt << 1 | 1]; }
void pushdown(int rt, int l, int r) {
  if (tag[rt] != -1) {
    int mid = (l + r) >> 1;
    sum[rt << 1] = tag[rt] * (mid - l + 1);
    sum[rt << 1 | 1] = tag[rt] * (r - mid);
    tag[rt << 1] = tag[rt];
    tag[rt << 1 | 1] = tag[rt];
    tag[rt] = 0;
  }
}

void build(int rt, int l, int r) {
  tag[rt] = -1;
  if (l == r) {
    sum[rt] = (node[l] <= n ? 1 : 0);
    // cout << rt << ' ' << l << ' ' << node[l] << ' ' << sum[rt] << endl;
    return;
  }
  int mid = (l + r) >> 1;
  build(rt << 1, l, mid);
  build(rt << 1 | 1, mid + 1, r);
  pushup(rt);
}

void modify(int rt, int l, int r, int L, int R, int v) {
  // cout << "M" << endl;
  if (L <= l && r <= R) {
    sum[rt] = v * (r - l + 1);
    tag[rt] = v;
    return;
  }
  pushdown(rt, l, r);
  int mid = (l + r) >> 1;
  if (L <= mid)
    modify(rt << 1, l, mid, L, R, v);
  if (R > mid)
    modify(rt << 1 | 1, mid + 1, r, L, R, v);
  pushup(rt);
}

ll query(int rt, int l, int r, int L, int R) {
  // cout << "Q" << endl;
  if (L <= l && r <= R)
    return sum[rt];
  pushdown(rt, l, r);
  int mid = (l + r) >> 1;
  ll ans = 0;
  if (L <= mid)
    ans += query(rt << 1, l, mid, L, R);
  if (R > mid)
    ans += query(rt << 1 | 1, mid + 1, r, L, R);
  return ans;
}

} // namespace SegTree

void getson(ll u, ll f) {
  dep[u] = dep[f] + 1;
  size[u] = 1;
  fa[u] = f;
  son[u] = 0;
  for (auto v : tree[u]) {
    if (v == f)
      continue;
    getson(v, u);
    size[u] += size[v];
    if (size[v] > size[son[u]])
      son[u] = v;
  }
}

void decompose(ll u, ll f) {
  top[u] = f;
  dfn[u] = ++idx;
  node[idx] = u;
  if (son[u])
    decompose(son[u], f);
  for (auto v : tree[u]) {
    if (v == fa[u] || v == son[u])
      continue;
    decompose(v, v);
  }
}

ll update(ll u, ll v) {
  // jump to the lca of u and v
  while (top[u] != top[v]) {
    cout << u << ' ' << v << endl;
    if (dep[top[u]] < dep[top[v]])
      swap(u, v);
    cout << dfn[top[u]] << ' ' << dfn[u] << endl;
    ans += SegTree::query(1, 1, n2, dfn[top[u]], dfn[u]);
    SegTree::modify(1, 1, n2, dfn[top[u]], dfn[u], 0);
    u = fa[top[u]];
  }
  if (dep[u] > dep[v])
    swap(u, v);
  ans += SegTree::query(1, 1, n2, dfn[u], dfn[v]);
  // cout << ans << endl;
  SegTree::modify(1, 1, n2, dfn[u], dfn[v], 0);
  return u;
}

void solve() {
  ans = -s;
  ll cur = pts[1];
  // build the segment tree
  // TODO: optimize the segment tree
  SegTree::build(1, 1, n2);
  for (int i = 2; i <= s; ++i) {
    // let cur be the node that is the closest to the root
    // then we can update the ans by the sum of weight between cur and pts[i]
    cur = update(cur, pts[i]);
    // cout << cur << ' ';
  }
  cout << ans << endl;
}

void run() {
  n2 = n + Tarjan::vbcccnt;
  // decompose the tree
  getson(1, 0);
  decompose(1, 1);
  cin >> q;
  for (int i = 1; i <= q; ++i) {
    cin >> s;
    for (int i = 1; i <= s; ++i)
      cin >> pts[i];
    solve();
  }
}

} // namespace Tree

void Tarjan::tarjan(long long u, long long fa) {
  dfn[u] = low[u] = ++idx;
  stk[++top] = u;
  for (auto v : graph[u]) {
    if (!dfn[v]) {
      tarjan(v, u);
      low[u] = min(low[u], low[v]);
    } else if (v != fa) {
      low[u] = min(low[u], dfn[v]);
    }
  }
  if (low[u] >= dfn[fa] && fa) {
    vbcccnt++;
    while (stk[top + 1] != u) {
      Tree::tree[vbcccnt + n].push_back(stk[top]);
      Tree::tree[stk[top]].push_back(vbcccnt + n);
      top--;
    }
    if (fa) {
      Tree::tree[fa].push_back(vbcccnt + n);
      Tree::tree[vbcccnt + n].push_back(fa);
    }
  }
}

void clear() {
  for (int i = 1; i <= n + Tarjan::vbcccnt; i++) {
    Tarjan::graph[i].clear();
    Tree::tree[i].clear();
  }
  Tarjan::idx = 0;
  Tarjan::top = 0;
  Tarjan::vbcccnt = 0;
  Tree::idx = 0;
  Tree::s = 0;
  Tree::ans = 0;
  memset(Tarjan::dfn, 0, sizeof(Tarjan::dfn));
  memset(Tarjan::low, 0, sizeof(Tarjan::low));
  memset(Tarjan::stk, 0, sizeof(Tarjan::stk));
  memset(Tree::dfn, 0, sizeof(Tree::dfn));
  memset(Tree::node, 0, sizeof(Tree::node));
  memset(Tree::top, 0, sizeof(Tree::top));
  memset(Tree::son, 0, sizeof(Tree::son));
  memset(Tree::fa, 0, sizeof(Tree::fa));
  memset(Tree::dep, 0, sizeof(Tree::dep));
  memset(Tree::size, 0, sizeof(Tree::size));
  memset(Tree::pts, 0, sizeof(Tree::pts));
  memset(Tree::SegTree::sum, 0, sizeof(Tree::SegTree::sum));
  memset(Tree::SegTree::tag, -1, sizeof(Tree::SegTree::tag));
}

void solve() {
  cin >> n >> m;
  for (int i = 1; i <= m; i++) {
    ll u, v;
    cin >> u >> v;
    Tarjan::graph[u].push_back(v);
    Tarjan::graph[v].push_back(u);
  }
  // the connectivity of the graph is guaranteed
  Tarjan::tarjan(1, 0);
  // then we can build the tree and solve the problem
  Tree::run();
}
int main() {
  ios::sync_with_stdio(0);
  cin.tie(nullptr);
  cout.tie(nullptr);
  cin >> T;
  while (T--) {
    clear();
    solve();
  }
  return 0;
}

/*
2
7 6
1 2
1 3
2 4
2 5
3 6
3 7
3
2 1 2
3 2 3 4
4 4 5 6 7
6 6
1 2
1 3
2 3
1 4
2 5
3 6
4
3 1 2 3
3 1 2 6
3 1 5 6
3 4 5 6


0
1
3
0
1
2
3
*/