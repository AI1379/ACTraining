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

void solve() {
  ull n;
  cin >> n;
  vector<pll> a(n);
  for (auto i = 0ull; i < n; ++i) {
    cin >> a[i].first;
    a[i].second = i;
  }
  sort(a.begin(), a.end());
  vector<ll> b(n), ans(n);
  for (auto i = 0ull; i < n; ++i) {
    b[i] = a[i].first;
  }
  auto m = unique(b.begin(), b.end()) - b.begin();
  ll idx = 0, pre_idx = 0, pre_val = 0;
  if (b[0] != 0) {
    cout << "-1\n";
    return;
  }
  for (auto i = 1; i < m; ++i) {
    idx = lower_bound(a.begin(), a.end(), make_pair(b[i], 0ll)) - a.begin();
    auto offset = idx - pre_idx;
    auto diff = b[i] - b[i - 1];
    if (diff % offset != 0) {
      cout << "-1\n";
      return;
    } else if (pre_val >= diff / offset) {
      cout << "-1\n";
      return;
    }
    for (auto i = pre_idx; i < idx; ++i) {
      ans[a[i].second] = diff / offset;
    }
    pre_idx = idx;
    pre_val = diff / offset;
  }
  for (auto i = pre_idx; i < n; ++i) {
    ans[a[i].second] = pre_val + 1;
  }
  for (auto i = 0ull; i < n; ++i) {
    cout << ans[i] << " ";
  }
  cout << "\n";
  return;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int t;
  cin >> t;
  while (t--) {
    solve();
  }
  return 0;
}