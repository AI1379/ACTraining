#include <bits/stdc++.h>
using namespace std;
#define ll long long
const ll MAXN = 100010;
struct Node {
  ll val, tag;
};
int n, m;
ll val[MAXN * 2];
Node segt[MAXN * 2];
int lowbit(int x) { return x & (-x); }
void build() {
  for (int i = 1; i <= n; ++i) {
    segt[n + i].val = val[i];
  }
  for (int i = n; i >= 1; --i) {
    segt[i].val = segt[i * 2].val + segt[i * 2 + 1].val;
  }
}
void pushup(int cur) {
  segt[cur].val = segt[cur * 2].val + segt[cur * 2 + 1].val;
}
void update(int l, int r, ll delta) {
  ll len = 1, llen = 0, rlen = 0;
  int p = l + n - 1, q = r + n + 1;
  for (; p / 2 != q / 2; p >>= 1, q >>= 1, len <<= 1) {
    // segt[p].val += llen * delta;
    // segt[q].val += rlen * delta;
    if (p < n) {
      pushup(p);
      pushup(q);
    }
    if (p % 2 == 0) {
      segt[p ^ 1].val += delta * len;
      segt[p ^ 1].tag += delta;
      // llen += len;
    }
    if (q % 2 == 1) {
      segt[q ^ 1].val += delta * len;
      segt[q ^ 1].tag += delta;
      // rlen += len;
    }
  }
  for (; p; p >>= 1, q >>= 1) {
    // segt[p].val += llen * delta;
    // segt[q].val += rlen * delta;
    pushup(p);
    pushup(q);
  }
}
ll query(int l, int r) {
  ll len = 1, llen = 0, rlen = 0, ans = 0;
  int p = l + n - 1, q = r + n + 1;
  for (; p / 2 != q / 2; p >>= 1, q >>= 1, len <<= 1) {
    ans += llen * segt[p].tag + rlen * segt[q].tag;
    if (p % 2 == 0) {
      ans += segt[p ^ 1].val;
      llen += len;
    }
    if (q % 2 == 1) {
      ans += segt[q ^ 1].val;
      rlen += len;
    }
  }
  for (; p; p >>= 1, q >>= 1) {
    ans += llen * segt[p].tag + rlen * segt[q].tag;
  }
  return ans;
}
int main() {
  ll op, u, v, d;
  ios::sync_with_stdio(false);
  cin >> n >> m;
  for (int i = 1; i <= n; ++i) {
    cin >> val[i];
  }
  while (lowbit(n) != n)
    n += lowbit(n);
  build();
  for (int i = 1; i <= m; ++i) {
    cin >> op >> u >> v;
    if (op == 1) {
      cin >> d;
      update(u, v, d);
    } else {
      cout << query(u, v) << endl;
    }
  }
  return 0;
}
/**
5 5
1 5 4 2 3
2 2 4
1 2 3 2
2 3 4
1 1 5 1
2 1 4
*/