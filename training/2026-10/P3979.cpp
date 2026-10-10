#include <bits/stdc++.h>
using namespace std;

#ifdef DEBUG
#define DOUT cerr
#else
#define DOUT                                                                   \
  if constexpr (false)                                                         \
  cerr
#endif

#define ll long long
#define ull unsigned long long
#define pll pair<ll, ll>
#define pull pair<ull, ull>

const ll MAXN = 100010;

ll n, m;
vector<ll> tree[MAXN];
ll siz[MAXN], top[MAXN], btm[MAXN], dfn[MAXN], prefer[MAXN], idx[MAXN];
ll dep[MAXN], fa[MAXN];
ll cur_dfn;
ll val[MAXN];
ll segt[MAXN * 4], tag[MAXN * 4];

void build(ll cur, ll nl, ll nr) {
  if (nl == nr) {
    segt[cur] = val[nl];
    return;
  }
  auto mid = (nl + nr) / 2;
  build(cur * 2, nl, mid);
  build(cur * 2 + 1, mid + 1, nr);
  segt[cur] = min(segt[cur * 2], segt[cur * 2 + 1]);
}

void pushdown(ll cur) {
  if (tag[cur]) {
    segt[cur * 2] = tag[cur];
    tag[cur * 2] = tag[cur];
    segt[cur * 2 + 1] = tag[cur];
    tag[cur * 2 + 1] = tag[cur];
    tag[cur] = 0;
  }
}

ll query(ll cur, ll nl, ll nr, ll ql, ll qr) {
  // DOUT << "query " << cur << ' ' << nl << ' ' << nr << ' ' << ql << ' ' << qr
  //  << endl;
  if (ql > qr)
    return 1ll << 60;
  if (ql <= nl && nr <= qr)
    return segt[cur];

  pushdown(cur);
  auto mid = (nl + nr) / 2;
  auto ans = 1ll << 60;
  if (ql <= mid)
    ans = min(ans, query(cur * 2, nl, mid, ql, qr));
  if (mid < qr)
    ans = min(ans, query(cur * 2 + 1, mid + 1, nr, ql, qr));
  return ans;
}

void modify(ll cur, ll nl, ll nr, ll ql, ll qr, ll nv) {
  // DOUT << "modify " << cur << ' ' << nl << ' ' << nr << ' ' << ql << ' ' <<
  // qr
  //  << ' ' << nv << endl;
  if (ql <= nl && nr <= qr) {
    tag[cur] = segt[cur] = nv;
    return;
  }
  pushdown(cur);
  auto mid = (nl + nr) / 2;
  if (ql <= mid)
    modify(cur * 2, nl, mid, ql, qr, nv);
  if (mid < qr)
    modify(cur * 2 + 1, mid + 1, nr, ql, qr, nv);
  segt[cur] = min(segt[cur * 2], segt[cur * 2 + 1]);
  return;
}

void get_prefer(ll u, ll p) {
  siz[u] = 1;
  dep[u] = dep[p] + 1;
  fa[u] = p;
  // DOUT << u << ' ' << p << endl;
  for (auto v : tree[u]) {
    if (v == p)
      continue;
    get_prefer(v, u);
    siz[u] += siz[v];
    if (siz[v] > siz[prefer[u]])
      prefer[u] = v;
  }
}

void decompose(ll u, ll tp) {
  dfn[u] = ++cur_dfn;
  idx[dfn[u]] = u;
  btm[u] = dfn[u];
  top[u] = tp;
  if (prefer[u]) {
    decompose(prefer[u], tp);
    btm[u] = max(btm[u], btm[prefer[u]]);
  }
  for (auto v : tree[u]) {
    if (v == fa[u] || v == prefer[u])
      continue;
    decompose(v, v);
    btm[u] = max(btm[u], btm[v]);
  }
}

void update_route(ll u, ll v, ll nv) {
  while (top[u] != top[v]) {
    // DOUT << "current u&v: " << u << ' ' << v << endl;
    if (dep[top[u]] < dep[top[v]])
      swap(u, v);
    // dep[top[u]] >= dep[top[v]]
    modify(1, 1, n, dfn[top[u]], dfn[u], nv);
    u = fa[top[u]];
  }
  if (dep[u] < dep[v])
    swap(u, v);
  modify(1, 1, n, dfn[v], dfn[u], nv);
}

ll get_v(ll u, ll rt) {
  auto v = rt;
  while (v) {
    if (dfn[top[v]] <= dfn[u] && dfn[u] <= dfn[v])
      // top[v], u, v are on the same chain. Note that dfn[u] will never equals
      // to dfn[v]
      return idx[dfn[u] + 1];
    if (fa[top[v]] == u)
      return top[v]; // u is the father of top[v]
    v = fa[top[v]];
  }
  return 0;
}

ll query_subtree(ll u, ll rt) {
  auto tot = query(1, 1, n, 1, n);
  if (u == rt)
    return tot;
  auto v = get_v(u, rt);
  if (v != 0) {
    auto ls = query(1, 1, n, 1, dfn[v] - 1);
    auto rs = query(1, 1, n, btm[v] + 1, n);
    return min(ls, rs);
  } else {
    return query(1, 1, n, dfn[u], btm[u]);
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  ll opt;
  ll u, v, w;
  ll cur_rt;
  cin >> n >> m;
  for (int i = 1; i <= n - 1; ++i) {
    cin >> u >> v;
    tree[u].emplace_back(v);
    tree[v].emplace_back(u);
  }
  get_prefer(1, 0);
  decompose(1, 1);

  for (int i = 1; i <= n; ++i) {
    cin >> val[dfn[i]];
  }
  build(1, 1, n);

  cin >> cur_rt;

  while (m--) {
    cin >> opt;
    if (opt == 1) {
      cin >> cur_rt;
    } else if (opt == 2) {
      cin >> u >> v >> w;
      update_route(u, v, w);
    } else if (opt == 3) {
      cin >> u;
      cout << query_subtree(u, cur_rt) << endl;
    }
  }

  return 0;
}