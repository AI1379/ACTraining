#include <bits/stdc++.h>
using namespace std;
#define ll long long
const ll MAXN = 100010;
struct Node {
  struct Info {
    ll val, len;
  } info;
  struct Tag {
    ll add;
  } tag;
};
ll lowbit(ll x) { return x & (-x); }
ll n, m, n0;
ll val[MAXN * 2];
Node segt[MAXN * 2];
Node::Info merge(Node::Info lhs, Node::Info rhs) {
  return Node::Info{lhs.val + rhs.val, lhs.len + rhs.len};
}
Node::Info merge(Node::Info info, Node::Tag tag) {
  return Node::Info{info.val + info.len * tag.add, info.len};
}
Node::Tag merge(Node::Tag pre, Node::Tag cur) {
  return Node::Tag{pre.add + cur.add};
}
void pushup(int cur) {
  segt[cur].info = merge(segt[cur * 2].info, segt[cur * 2 + 1].info);
  segt[cur].info = merge(segt[cur].info, segt[cur].tag);
}
void build() {
  for (int i = 1; i <= n; ++i) {
    segt[i + n].info = Node::Info{val[i], 1};
  }
  for (int i = n; i >= 1; --i) {
    pushup(i);
  }
}
void update(int l, int r, Node::Tag tag) {
  int p = l + n - 1, q = r + n + 1;
  for (; p / 2 != q / 2; p >>= 1, q >>= 1) {
    if (p < n) {
      pushup(p);
      pushup(q);
    }
    if (p % 2 == 0) {
      segt[p ^ 1].info = merge(segt[p ^ 1].info, tag);
      segt[p ^ 1].tag = merge(segt[p ^ 1].tag, tag);
    }
    if (q % 2 == 1) {
      segt[q ^ 1].info = merge(segt[q ^ 1].info, tag);
      segt[q ^ 1].tag = merge(segt[q ^ 1].tag, tag);
    }
  }
  for (; p; p >>= 1, q >>= 1) {
    pushup(p);
    pushup(q);
  }
}
Node::Info query(int l, int r) {
  int p = l + n - 1, q = r + n + 1;
  Node::Info linfo = {0, 0}, rinfo = {0, 0};
  for (; p / 2 != q / 2; p >>= 1, q >>= 1) {
    linfo = merge(linfo, segt[p].tag);
    rinfo = merge(rinfo, segt[q].tag);
    if (p % 2 == 0) {
      linfo = merge(linfo, segt[p ^ 1].info);
    }
    if (q % 2 == 1) {
      rinfo = merge(rinfo, segt[q ^ 1].info);
    }
  }
  for (; p; p >>= 1, q >>= 1) {
    linfo = merge(linfo, segt[p].tag);
    rinfo = merge(rinfo, segt[q].tag);
  }
  return merge(linfo, rinfo);
}
int main() {
  ll op, u, v, w;
  ios::sync_with_stdio(false);
  cin >> n >> m;
  n0 = n;
  for (int i = 1; i <= n0; ++i) {
    cin >> val[i];
  }
  while (n != lowbit(n))
    n += lowbit(n);
  build();
  for (int i = 1; i <= m; ++i) {
    cin >> op >> u >> v;
    if (op == 1) {
      cin >> w;
      update(u, v, Node::Tag{w});
    } else if (op == 2) {
      cout << query(u, v).val << endl;
    }
  }
  return 0;
}