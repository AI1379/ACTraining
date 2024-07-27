#include <bits/stdc++.h>
using namespace std;
#define ll int
#define lson (cur * 2)
#define rson (cur * 2 + 1)
const ll MAXX = 40000;
const ll MAXN = 100010;
const double eps = 1e-9;
const double INF = 1e9;
const ll MOD1 = 39989;
const ll MOD2 = 1000000000;
struct Node {
  int l, r;
  int id;
};
Node segt[MAXX * 4];
double k[MAXN], b[MAXN];
int cnt;
int cmp(double lhs, double rhs) {
  if (lhs - rhs > eps)
    return 1;
  if (rhs - lhs > eps)
    return -1;
  return 0;
}
double calc(int id, int x) { return id == INF ? -INF : x * k[id] + b[id]; }
void insert(int x0, int y0, int x1, int y1) {
  ++cnt;
  if (x0 == x1) {
    k[cnt] = 0;
    b[cnt] = max(y0, y1);
  } else {
    k[cnt] = 1.0 * (y1 - y0) / (x1 - x0);
    b[cnt] = y0 - k[cnt] * x0;
  }
}
void update(int cur, int id) {
  auto mid = (segt[cur].l + segt[cur].r) / 2;
  int bmid = cmp(calc(id, mid), calc(segt[cur].id, mid));
  if (bmid == 1 || (bmid == 0 && id < segt[cur].id))
    swap(id, segt[cur].id);
  auto bl = cmp(calc(id, segt[cur].l), calc(segt[cur].id, segt[cur].l));
  auto br = cmp(calc(id, segt[cur].r), calc(segt[cur].id, segt[cur].r));
  if (bl == 1 || (bl == 0 && id < segt[cur].id))
    update(lson, id);
  if (br == 1 || (br == 0 && id < segt[cur].id))
    update(rson, id);
  return;
}
void build(int cur, int l, int r) {
  segt[cur].l = l;
  segt[cur].r = r;
  segt[cur].id = INF;
  if (l == r)
    return;
  auto mid = (l + r) / 2;
  build(lson, l, mid);
  build(rson, mid + 1, r);
}
void modify(int cur, int l, int r, int id) {
  if (l <= segt[cur].l && segt[cur].r <= r) {
    update(cur, id);
    return;
  }
  auto mid = (segt[cur].l + segt[cur].r) / 2;
  if (l <= mid)
    modify(lson, l, r, id);
  if (mid + 1 <= r)
    modify(rson, l, r, id);
  return;
}
int query(int cur, int k) {
  auto mid = (segt[cur].l + segt[cur].r) / 2;
  if (segt[cur].l == k && segt[cur].r == k) {
    return segt[cur].id;
  }
  auto check = [k](int a, int b) {
    auto c = cmp(calc(a, k), calc(b, k));
    return c == 0 ? a > b : c == -1;
  };
  if (k <= mid)
    return max(query(lson, k), segt[cur].id, check);
  else
    return max(query(rson, k), segt[cur].id, check);
}
int main() {
  ios::sync_with_stdio(false);
  int n, lastans = 0;
  build(1, 1, MAXX);
  cin >> n;
  while (n--) {
    int op;
    cin >> op;
    if (op == 1) {
      int x0, y0, x1, y1;
      cin >> x0 >> y0 >> x1 >> y1;
      x0 = (x0 + lastans - 1 + MOD1) % MOD1 + 1,
      x1 = (x1 + lastans - 1 + MOD1) % MOD1 + 1;
      y0 = (y0 + lastans - 1 + MOD2) % MOD2 + 1,
      y1 = (y1 + lastans - 1 + MOD2) % MOD2 + 1;
      if (x0 > x1)
        swap(x0, x1), swap(y0, y1);
      insert(x0, y0, x1, y1);
      modify(1, x0, x1, cnt);
    } else {
      int x;
      cin >> x;
      x = (x + lastans - 1 + MOD1) % MOD1 + 1;
      lastans = query(1, x);
      lastans = (lastans == INF ? 0 : lastans);
      cout << lastans << endl;
    }
  }
  return 0;
}