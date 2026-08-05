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

void solve() {
  int n;
  cin >> n;

  vector<ll> a(n + 1);
  ll total = 0;
  for (int i = 1; i <= n; ++i) {
    cin >> a[i];
    total += a[i];
  }

  vector<int> parent(n + 1, 0);
  vector<int> childCount(n + 1, 0);
  for (int i = 2; i <= n; ++i) {
    cin >> parent[i];
    ++childCount[parent[i]];
  }

  int leaves = 0;
  for (int i = 1; i <= n; ++i) {
    if (childCount[i] == 0) {
      ++leaves;
    }
  }

  vector<int> fa(n + 1);
  fa[0] = 0;
  for (int u = 1; u <= n; ++u) {
    if (childCount[u] > 0) {
      fa[u] = u;
    } else {
      fa[u] = parent[u];
    }
  }
  function<int(int)> find = [&](int x) {
    return fa[x] == x ? x : fa[x] = find(fa[x]);
  };

  vector<int> order(n);
  iota(order.begin(), order.end(), 1);
  sort(order.begin(), order.end(), [&](int x, int y) {
    if (a[x] != a[y])
      return a[x] < a[y];
    return x < y;
  });

  vector<ll> losses;
  losses.reserve(n - leaves);
  for (int u : order) {
    int slot = find(u);
    if (slot == 0) {
      continue;
    }
    losses.push_back(a[u]);
    fa[slot] = find(parent[slot]);
  }

  vector<ll> prefix(losses.size() + 1, 0);
  for (int i = 0; i < (int)losses.size(); ++i) {
    prefix[i + 1] = prefix[i] + losses[i];
  }

  for (int k = 1; k <= n; ++k) {
    ll answer;
    if (k < leaves) {
      answer = -1;
    } else {
      int removedGroups = n - k;
      answer = total - prefix[removedGroups];
    }
    if (k > 1) {
      cout << ' ';
    }
    cout << answer;
  }
  cout << '\n';
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
