# G - Solution

## Hint 1

考虑每一组 $(a_i,\ b_i)$ 。容易注意到：这一组数无论如何变换，总是 $a_i$ 与 $b_i$ 配对。我们将这样的一组数记作 `pair[i]`。这是因为，题目里面的交换操作实际上只是将两组 `pair` 交换，然后对一组 `pair` 做一次翻转。

## Hint 2

考虑能否将两组 `pair` 交换而不使这两组数翻转。这是可以做到的。如图：

![](https://codeforces.com/predownloaded/5b/1d/5b1d12611f7a23c2afe87588dc7ba673fe994114.png)

## Hint 3

考虑能否将两组 `pair` 翻转而不使它们对换。这也是可以做到的。如图：

![](https://codeforces.com/predownloaded/9f/d9/9fd9532ea99dea2d7d2b8e764120f67f506f20f3.png)

## Hint 4

考虑能否将一组 `pair` 翻转而不改变其他的 `pair`。这是做不到的。容易注意到，任意多次操作后，被翻转的位数必然是偶数，故无法将一组 `pair` 翻转而不改变其他位。

## Solution

首先我们记 $m_i = \min(a_i,\ b_i)$ 。我们断言：最终的结果一定是按照 $m_i$ 升序排列的。否则，假如存在有一位的 $m_i < m_{i-1}$，那么容易发现 $a$ 与 $b$ 中必然有一个是降序的，这违反了题目设定。

同时，我们已经证明了，我们可以将两组数对换而不翻转它们，因此可以先对 `pair` 做一次按照 `m[i]` 的排序，然后考虑能否通过翻转使得它们排成一个升序排列。

此时考虑 `dp`，设计状态如下：

- `dp[i][1] == 1` 表示到第 `i` 位为止，可以通过偶数次翻转使得此前每一位都满足题目条件，且不翻转第 `i` 位

- `dp[i][2] == 1` 表示偶数次翻转且翻转第 `i` 位。

- `dp[i][3] == 1` 表示奇数次翻转且不翻转第 `i` 位。

- `dp[i][4] == 1` 表示奇数次翻转且翻转第 `i` 位。

当然也可以设计成 `dp[n][0/1][0/1]` 这样的状态。两种做法显然是等价的。如果你神通广大，也可以用位运算压缩到一个 `unsigned char` 以内，当然这并不是必要的。

然后考虑初始值。易得 `dp[1][1] = dp[1][4] = 1`。

最后考虑状态转移。我们考虑一个局部的情况 `pair[i-1]` 和 `pair[i]`。此时有两种情况：

- `pair[i-1].first < pair[i].first && pair[i-1].second < pair[i].second`。此时有状态转移：

  - `dp[i][1] |= dp[i-1][1]`
  - `dp[i][2] |= dp[i-1][4]`
  - `dp[i][3] |= dp[i-1][3]`
  - `dp[i][4] |= dp[i-1][2]`

  这是因为此时 `pair[i-1]` 和 `pair[i]` 的翻转情况必须相同。

- `pair[i-1].second < pair[i].first && pair[i-1].first < pair[i].second`。此时有状态转移：

  - `dp[i][1] |= dp[i-1][2]`
  - `dp[i][2] |= dp[i-1][3]`
  - `dp[i][3] |= dp[i-1][4]`
  - `dp[i][4] |= dp[i-1][1]`

  这四个状态转移同理。

从而可以写出完整的 `dp` 过程。

最后，注意多测。

## Code - C++

```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pll pair<ll, ll>
const ll INF = 1ll << 62;
void solve() {
  ll n;
  cin >> n;
  vector<pll> val(n);
  vector<array<bool, 5>> dp(n);
  for (auto i = 0; i < n; ++i)
    cin >> val[i].first;
  for (auto j = 0; j < n; ++j)
    cin >> val[j].second;
  sort(val.begin(), val.end(), [](pll lhs, pll rhs) {
    return min(lhs.first, lhs.second) < min(rhs.first, rhs.second);
  });
  dp[0][1] = dp[0][4] = true;
  for (auto i = 1; i < n; ++i) {
    if (val[i - 1].first < val[i].first && val[i - 1].second < val[i].second) {
      dp[i][1] |= dp[i - 1][1];
      dp[i][2] |= dp[i - 1][4];
      dp[i][3] |= dp[i - 1][3];
      dp[i][4] |= dp[i - 1][2];
    }
    if (val[i - 1].first < val[i].second && val[i - 1].second < val[i].first) {
      dp[i][1] |= dp[i - 1][2];
      dp[i][2] |= dp[i - 1][3];
      dp[i][3] |= dp[i - 1][4];
      dp[i][4] |= dp[i - 1][1];
    }
  }
  cout << ((dp[n - 1][1] || dp[n - 1][2]) ? "YES" : "NO") << endl;
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

## Code - Python

```python
def solve():
    n = int(input())
    val = []
    first_vals = list(map(int, input().split()))
    second_vals = list(map(int, input().split()))
    for i in range(n):
        val.append((int(first_vals[i]), int(second_vals[i])))
    val.sort(key=lambda x: min(x[0], x[1]))

    dp = [[False]*5 for _ in range(n)]
    dp[0][1] = True
    dp[0][4] = True
    for i in range(1, n):
        if val[i-1][0] < val[i][0] and val[i-1][1] < val[i][1]:
            dp[i][1] |= dp[i-1][1]
            dp[i][2] |= dp[i-1][4]
            dp[i][3] |= dp[i-1][3]
            dp[i][4] |= dp[i-1][2]
        if val[i-1][0] < val[i][1] and val[i-1][1] < val[i][0]:
            dp[i][1] |= dp[i-1][2]
            dp[i][2] |= dp[i-1][3]
            dp[i][3] |= dp[i-1][4]
            dp[i][4] |= dp[i-1][1]

    print("YES\n" if (dp[n-1][1] or dp[n-1][2]) else "NO\n")


if __name__ == '__main__':
    t = int(input())
    for _ in range(t):
        solve()
        
```