#include <bits/stdc++.h>
#include <ratio>
using namespace std;
#define ll long long
const ll MAXN = 500010;
const ll INF = (1ll << 60);
struct Node {
  ll l, r, mid;
  ll sum, cmax, hmax, secmax, cnt;
  ll tag, maxtag, tag2, maxtag2;
};
ll n, m;
ll a[MAXN];
Node segt[MAXN * 4];
#define lson (cur * 2)
#define rson (cur * 2 + 1)
#define sgmid (segt[cur].mid)
#define nlen(x) (segt[(x)].r - segt[(x)].l + 1)
void update(ll cur, ll tag, ll maxtag, ll tag2, ll maxtag2) {
  segt[cur].hmax = max(segt[cur].hmax, segt[cur].cmax + maxtag2);
  segt[cur].cmax += tag2;
  segt[cur].sum += tag * (nlen(cur) - segt[cur].cnt) + tag2 * segt[cur].cnt;
  if (segt[cur].secmax != -INF)
    segt[cur].secmax += tag;
  segt[cur].maxtag = max(segt[cur].maxtag, segt[cur].tag + maxtag);
  segt[cur].maxtag2 = max(segt[cur].maxtag2, segt[cur].tag2 + maxtag2);
  segt[cur].tag += tag;
  segt[cur].tag2 += tag2;
}
void pushdown(ll cur) {
  ll cmax = max(segt[lson].cmax, segt[rson].cmax);
  if (segt[lson].cmax == cmax)
    update(lson, segt[cur].tag, segt[cur].maxtag, segt[cur].tag2,
           segt[cur].maxtag2);
  else
    update(lson, segt[cur].tag, segt[cur].maxtag, segt[cur].tag,
           segt[cur].maxtag);
  if (segt[rson].cmax == cmax)
    update(rson, segt[cur].tag, segt[cur].maxtag, segt[cur].tag2,
           segt[cur].maxtag2);
  else
    update(rson, segt[cur].tag, segt[cur].maxtag, segt[cur].tag,
           segt[cur].maxtag);
  segt[cur].tag = segt[cur].maxtag = segt[cur].tag2 = segt[cur].maxtag2 = 0;
}
void pushup(ll cur) {
  segt[cur].sum = segt[lson].sum + segt[rson].sum;
  segt[cur].cmax = max(segt[lson].cmax, segt[rson].cmax);
  segt[cur].hmax = max(segt[lson].hmax, segt[rson].hmax);
  segt[cur].secmax = max(segt[lson].cmax == segt[rson].cmax
                             ? -INF
                             : min(segt[lson].cmax, segt[rson].cmax),
                         max(segt[lson].secmax, segt[rson].secmax));
  segt[cur].cnt = 0;
  if (segt[lson].cmax == segt[cur].cmax)
    segt[cur].cnt += segt[lson].cnt;
  if (segt[rson].cmax == segt[cur].cmax)
    segt[cur].cnt += segt[rson].cnt;
}
void build(ll cur, ll l, ll r) {
  segt[cur].l = l;
  segt[cur].r = r;
  segt[cur].mid = (l + r) / 2;
  if (l == r) {
    segt[cur].sum = segt[cur].cmax = segt[cur].hmax = a[l];
    segt[cur].secmax = -INF;
    segt[cur].cnt = 1;
    return;
  }
  build(lson, l, sgmid);
  build(rson, sgmid + 1, r);
  pushup(cur);
}
ll querysum(ll cur, ll l, ll r) {
  if (l <= segt[cur].l && segt[cur].r <= r) {
    return segt[cur].sum;
  }
  ll res = 0;
  pushdown(cur);
  if (l <= sgmid)
    res += querysum(lson, l, r);
  if (sgmid + 1 <= r)
    res += querysum(rson, l, r);
  return res;
}
ll querymax(ll cur, ll l, ll r) {
  if (l <= segt[cur].l && segt[cur].r <= r) {
    return segt[cur].cmax;
  }
  ll res = -INF;
  pushdown(cur);
  if (l <= sgmid)
    res = max(res, querymax(lson, l, r));
  if (sgmid + 1 <= r)
    res = max(res, querymax(rson, l, r));
  return res;
}
ll queryhismax(ll cur, ll l, ll r) {
  if (l <= segt[cur].l && segt[cur].r <= r) {
    return segt[cur].hmax;
  }
  ll res = -INF;
  pushdown(cur);
  if (l <= sgmid)
    res = max(res, queryhismax(lson, l, r));
  if (sgmid + 1 <= r)
    res = max(res, queryhismax(rson, l, r));
  return res;
}
void modifysum(ll cur, ll l, ll r, ll k) {
  if (l <= segt[cur].l && segt[cur].r <= r) {
    segt[cur].tag += k;
    segt[cur].maxtag = max(segt[cur].maxtag, segt[cur].tag);
    segt[cur].tag2 += k;
    segt[cur].maxtag2 = max(segt[cur].maxtag2, segt[cur].tag2);
    segt[cur].sum += k * nlen(cur);
    segt[cur].cmax += k;
    segt[cur].hmax = max(segt[cur].hmax, segt[cur].cmax);
    if (segt[cur].secmax != -INF)
      segt[cur].secmax += k;
    return;
  }
  pushdown(cur);
  if (l <= sgmid)
    modifysum(lson, l, r, k);
  if (sgmid + 1 <= r)
    modifysum(rson, l, r, k);
  pushup(cur);
}
void modifymin(ll cur, ll l, ll r, ll v) {
  if (segt[cur].cmax <= v)
    return;
  if ((l <= segt[cur].l && segt[cur].r <= r) && segt[cur].secmax < v) {
    ll d = segt[cur].cmax - v;
    segt[cur].cmax = v;
    segt[cur].sum -= d * segt[cur].cnt;
    segt[cur].tag2 -= d;
    return;
  }
  pushdown(cur);
  if (l <= sgmid)
    modifymin(lson, l, r, v);
  if (sgmid + 1 <= r)
    modifymin(rson, l, r, v);
  pushup(cur);
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  ll op, l, r, v;
  cin >> n >> m;
  for (int i = 1; i <= n; ++i)
    cin >> a[i];
  build(1, 1, n);
  while (m--) {
    cin >> op;
    switch (op) {
    case 1: {
      cin >> l >> r >> v;
      modifysum(1, l, r, v);
      break;
    }
    case 2: {
      cin >> l >> r >> v;
      modifymin(1, l, r, v);
      break;
    }
    case 3: {
      cin >> l >> r;
      cout << querysum(1, l, r) << '\n';
      break;
    }
    case 4: {
      cin >> l >> r;
      cout << querymax(1, l, r) << '\n';
      break;
    }
    case 5: {
      cin >> l >> r;
      cout << queryhismax(1, l, r) << '\n';
      break;
    }
    }
  }
  return 0;
}