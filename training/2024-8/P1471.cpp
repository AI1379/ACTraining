#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define ld long double
#define pdd pair<ld, ld>
#define lson (cur * 2)
#define rson (cur * 2 + 1)
#define nlen(p) (segt[(p)].r - segt[(p)].l + 1)
const ll MAXN = 100010;
struct Node {
  ll l, r;
  pdd info; // (sum, square_sum)
  ld tag;
};
ll n, m;
ld val[MAXN];
Node segt[MAXN * 4];
pdd merge(pdd lhs, pdd rhs) {
  return make_pair(lhs.first + rhs.first, lhs.second + rhs.second);
}
pdd merge(pdd info, ld tag, ll len) {
  info.second += 2 * tag * info.first + tag * tag * len;
  info.first += tag * len;
  return info;
}
ld merge(ld pre, ld cur) { return pre + cur; }
void pushup(ll cur) {
  segt[cur].info = merge(segt[lson].info, segt[rson].info);
}
void pushdown(ll cur) {
  if (fabs(segt[cur].tag) > 1e-16) {
    segt[lson].info = merge(segt[lson].info, segt[cur].tag, nlen(lson));
    segt[rson].info = merge(segt[rson].info, segt[cur].tag, nlen(rson));
    segt[lson].tag = merge(segt[lson].tag, segt[cur].tag);
    segt[rson].tag = merge(segt[rson].tag, segt[cur].tag);
    segt[cur].tag = 0;
  }
}
void build(ll cur, ll l, ll r) {
  segt[cur].l = l, segt[cur].r = r;
  if (l == r) {
    segt[cur].info = {val[l], val[l] * val[l]};
    segt[cur].tag = 0;
    return;
  }
  auto mid = (l + r) / 2;
  build(lson, l, mid);
  build(rson, mid + 1, r);
  pushup(cur);
}
void modify(ll cur, ll l, ll r, ld tag) {
  if (l <= segt[cur].l && segt[cur].r <= r) {
    segt[cur].info = merge(segt[cur].info, tag, nlen(cur));
    segt[cur].tag = merge(segt[cur].tag, tag);
    return;
  }
  auto mid = (segt[cur].l + segt[cur].r) / 2;
  pushdown(cur);
  if (l <= mid)
    modify(lson, l, r, tag);
  if (mid + 1 <= r)
    modify(rson, l, r, tag);
  pushup(cur);
  return;
}
pdd query(ll cur, ll l, ll r) {
  if (l <= segt[cur].l && segt[cur].r <= r)
    return segt[cur].info;
  auto mid = (segt[cur].l + segt[cur].r) / 2;
  pushdown(cur);
  pdd res{0, 0};
  if (l <= mid)
    res = merge(res, query(lson, l, r));
  if (mid + 1 <= r)
    res = merge(res, query(rson, l, r));
  return res;
}
void print(ll cur) {
  cout << cur << ' ' << segt[cur].l << ' ' << segt[cur].r << ' '
       << segt[cur].info.first << ' ' << segt[cur].info.second << ' '
       << segt[cur].tag << endl;
  if (lson <= n * 4)
    print(lson);
  if (rson <= n * 4)
    print(rson);
}
int main() {
  ios::sync_with_stdio(false);
  ll op, u, v;
  ld w;
  cin >> n >> m;
  for (int i = 1; i <= n; ++i)
    cin >> val[i];
  build(1, 1, n);
  for (int i = 1; i <= m; ++i) {
    cin >> op >> u >> v;
    if (op == 1) {
      cin >> w;
      modify(1, u, v, w);
    } else if (op == 2) {
      auto s = query(1, u, v).first;
      // cout << s << ' ';
      cout << fixed << setprecision(4) << s / (ld)(v - u + 1) << endl;
    } else if (op == 3) {
      auto [s, sqs] = query(1, u, v);
      auto len = (ld)(v - u + 1);
      auto d = (sqs / len) - (s / len) * (s / len);
      // cout << s << ' ' << sqs << ' ' << d << ' ' << len << ' ';
      cout << fixed << setprecision(4) << d << endl;
    }
    // print(1);
  }
  return 0;
}