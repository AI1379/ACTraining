#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
#define ll long long
#define pll pair<ll, ll>
const ll INF = 1ll << 62;
const ll MAXN = 200010;
ll test_cases;
using RBTree = __gnu_pbds::tree<pll, __gnu_pbds::null_type, less<pll>,
                                __gnu_pbds::rb_tree_tag,
                                __gnu_pbds::tree_order_statistics_node_update>;
ll n, k;
pll val[MAXN];
ll ans = 0;
void solve() {
  RBTree tree;
  ans = 0;
  cin >> n >> k;
  for (int i = 1; i <= n; ++i)
    cin >> val[i].first;
  for (int i = 1; i <= n; ++i)
    cin >> val[i].second;
  sort(val + 1, val + n + 1,
       [](pll lhs, pll rhs) { return lhs.second > rhs.second; });
  for (ll i = 1; i <= n; ++i) {
    tree.insert({val[i].first, i});
    // if (val[i].second == val[i + 1].second)
    //   continue;
    auto it = tree.find_by_order(k);
    // auto lbit = tree.lower_bound({it->first, 0});
    // if (lbit != it)
    // it = --lbit;
    ll price = it->first;
    if (price > val[i].second || i <= k)
      price = val[i].second;
    cout << price << ' ' << val[i].second << ' ' << val[i + 1].second << ' '
         << i << ' ' << price * i << endl;
    if (price <= val[i + 1].second)
      continue;
    ans = max(ans, price * i);
  }
  cout << ans << endl;
  fill(val + 1, val + n + 1, pll{0, 0});
}
int main() {
  ios::sync_with_stdio(false);
  cin >> test_cases;
  while (test_cases--) {
    solve();
  }
  return 0;
}
/*
5
2 0
2 1
3 4
1 1
2
5
3 3
1 5 2
3 6 4
4 3
2 3 2 8
3 7 3 9
3 1
2 9 5
12 14 9

2
5
9
14
15


*/