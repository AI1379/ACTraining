# E - sol

在这个题目里我们不需要处理图本身的具体性质，而只关心点于点的连通性。因此，我们很容易地可以想到一个数据结构：并查集。也是因为这一点，在这个题目里面，我们完全没有必要使用传统的邻接表方式存图，而只需要存边即可。

接着，构造两个并查集，`FSet` 和 `GSet`，分别维护 `F` 和 `G` 的连通性。读入的时候可以直接把 `GSet` 构造完成。

然后先考虑删边。对于任意的一组 `F` 中的边，我们考虑 `G` 中这条边连接的两个点是否连通。如果不连通，那么这一条边必须要被删掉。否则，这条边就在删边后的图中被保留下来了，因此需要做一次 `merge`，表示这这两个点已经连通了。

接着，考虑加边。方法是类似的。对于任意的一条 `G` 中的边，考虑删边后的 `F` 中这两点是否连通，如果不连通则加边，同时统计答案。

容易证明，这个贪心策略就是最优解。

注意多测，注意并查集的初始化。

C++代码如下：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pll pair<ll, ll>
const ll INF = 1ll << 62;
void solve() {
  ll n, m1, m2, u, v, ans = 0;
  cin >> n >> m1 >> m2;
  vector<pll> F(m1), G(m2);
  vector<ll> GSet(n + 1), FSet(n + 1);
  for (int i = 1; i <= n; ++i) {
    FSet[i] = GSet[i] = i;
  }
  function<ll(vector<ll> &, ll)> find = [&](vector<ll> &S, ll x) {
    return S[x] == x ? x : S[x] = find(S, S[x]);
  };
  auto merge = [&](vector<ll> &S, ll x, ll y) {
    if (find(S, x) != find(S, y))
      S[find(S, x)] = find(S, y);
  };
  for (int i = 1; i <= m1; ++i) {
    cin >> u >> v;
    F.emplace_back(u, v);
  }
  for (int i = 1; i <= m2; ++i) {
    cin >> u >> v;
    merge(GSet, u, v);
    G.emplace_back(u, v);
  }
  for (auto [u, v] : F) {
    if (find(GSet, u) != find(GSet, v))
      ++ans;
    else
      merge(FSet, u, v);
  }
  for (auto [u, v] : G) {
    if (find(FSet, u) != find(FSet, v)) {
      merge(FSet, u, v);
      ++ans;
    }
  }
  cout << ans << endl;
}
int main() {
  ll test_cases;
  ios::sync_with_stdio(false);
  cin >> test_cases;
  while (test_cases--) {
    solve();
  }
  return 0;
}
```
