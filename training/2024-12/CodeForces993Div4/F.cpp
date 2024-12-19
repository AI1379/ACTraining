#include <algorithm>
#include <bits/stdc++.h>
using namespace std;
#define ll long long
const ll MAXN = 200010;
ll n, m, q;
ll a[MAXN], b[MAXN];
ll sa = 0, sb = 0, s;
ll x;
set<ll> mpa, mpb;
bool check(ll x) {
  for (int i = 1; i * i <= abs(x); ++i) {
    if (x % i == 0) {
      if (mpa.find(i) != mpa.end() && mpb.find(x / i) != mpb.end())
        return true;
      else if (mpa.find(x / i) != mpa.end() && mpb.find(i) != mpb.end())
        return true;
      else if (mpa.find(-i) != mpa.end() && mpb.find(-x / i) != mpb.end())
        return true;
      else if (mpa.find(-x / i) != mpa.end() && mpb.find(-i) != mpb.end())
        return true;
    }
  }
  return false;
}
int main() {
  ios::sync_with_stdio(false);
  cin >> n >> m >> q;
  for (int i = 1; i <= n; ++i) {
    cin >> a[i];
    sa += a[i];
  }
  for (int i = 1; i <= m; ++i) {
    cin >> b[i];
    sb += b[i];
  }
  s = sa * sb;
  for (int i = 1; i <= n; ++i)
    mpa.insert(sa - a[i]);
  for (int i = 1; i <= m; ++i)
    mpb.insert(sb - b[i]);
  while (q--) {
    cin >> x;
    if (check(x))
      cout << "YES\n";
    else
      cout << "NO\n";
  }
  return 0;
}