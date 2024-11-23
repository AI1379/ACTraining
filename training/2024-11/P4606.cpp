#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pll pair<ll, ll>
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
ll pts[MAXN * 2], s = 0;
ll pre[MAXN * 2];
ll ans = 0;

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

pll update(ll u, ll v) {
  ll res = 0;
  while (top[u] != top[v]) {
    if (dep[top[u]] < dep[top[v]])
      swap(u, v);
    res += pre[dfn[u]] - pre[dfn[top[u]] - 1];
    u = fa[top[u]];
  }
  if (dfn[u] > dfn[v])
    swap(u, v);
  res += pre[dfn[v]] - pre[dfn[u] - 1];
  return {res, u};
}

void solve() {
  sort(pts + 1, pts + s + 1, [](int a, int b) { return dfn[a] < dfn[b]; });
  ans = 0;
  pts[0] = pts[s];
  for (int i = 1; i <= s; ++i) {
    // cout << pts[i] << ' ' << dfn[pts[i]] << endl;
    auto [res, lca] = update(pts[i - 1], pts[i]);
    ans += res - (lca <= n ? 1 : 0);
  }
  ans /= 2;
  ans += (update(pts[1], pts[s]).second <= n ? 1 : 0);
  ans -= s;
  cout << ans << endl;
}

void run() {
  n2 = n + Tarjan::vbcccnt;
  // decompose the tree
  getson(1, 0);
  decompose(1, 1);
  for (int i = 1; i <= n2; ++i) {
    pre[i] = pre[i - 1] + (node[i] <= n ? 1 : 0);
    // cout << i << ' ' << node[i] << ' ' << pre[i] << endl;
  }
  cin >> q;
  for (int i = 1; i <= q; ++i) {
    cin >> s;
    for (int j = 1; j <= s; ++j)
      cin >> pts[j];
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
  for (int i = 1; i <= n; ++i)
    Tarjan::graph[i].clear();
  for (int i = 1; i <= n + Tarjan::vbcccnt; i++)
    Tree::tree[i].clear();
  Tarjan::idx = 0;
  Tarjan::top = 0;
  Tarjan::vbcccnt = 0;
  Tree::idx = 0;
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
  memset(Tree::pre, 0, sizeof(Tree::pre));
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