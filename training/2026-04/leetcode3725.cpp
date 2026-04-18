#include <bits/stdc++.h>

#include <algorithm>

using namespace std;

#ifdef DEBUG
#define DOUT cerr
#else
#define DOUT \
  if constexpr (false) cerr
#endif

#define ll long long

class Solution {
 public:
  static int gcd(int a, int b) {
    if (a < b) return gcd(b, a);
    return gcd(b, a % b);
  }
  static constexpr int MAXV = 50010;
  static constexpr int MOD = 1e9 + 7;
  static int count(const vector<int>& v, int x) {
    return upper_bound(v.begin(), v.end(), x) -
           lower_bound(v.begin(), v.end(), x);
  }
  int countCoprime(vector<vector<int>>& mat) {
    static ll f[MAXV], g[MAXV];
    memset(f, 0, sizeof(f));
    memset(g, 0, sizeof(g));

    int max_val = 0, n = mat.size();

    for (auto& row : mat) {
      sort(row.begin(), row.end());
      max_val = max(max_val, *max_element(row.begin(), row.end()));
    }
    ll tot;
    for (int d = max_val; d >= 1; --d) {
      f[d] = 1;
      for (int i = 0; i < n; ++i) {
        tot = 0;
        for (int k = 1; k * d <= max_val; ++k) {
          tot += count(mat[i], k * d);
        }
        f[d] = f[d] * tot % MOD;
        if (f[d] == 0) break;
      }
      g[d] = f[d];
      for (int k = 2; k * d <= max_val; ++k) {
        g[d] = (g[d] - g[k * d] + MOD) % MOD;
      }
    }
    return g[1];
  }
};

int main() {
  int n, m, x;
  cin >> n >> m;
  vector<vector<int>> mat(n, vector<int>(m));
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      cin >> mat[i][j];
    }
  }
  Solution sol;
  cout << sol.countCoprime(mat) << endl;

  return 0;
}