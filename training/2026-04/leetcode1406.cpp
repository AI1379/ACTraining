#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  static constexpr int MAXN = 50010;
  int dp[MAXN];
  string stoneGameIII(vector<int>& stoneValue) {
    int n = stoneValue.size();
    vector<int> dp(n + 3, INT_MIN / 2);

    dp[n] = 0;
    dp[n + 1] = 0;
    dp[n + 2] = 0;

    for (int i = n - 1; i >= 0; --i) {
      int currentTakeSum = 0;
      for (int k = 0; k < 3; ++k) {
        if (i + k < n) {
          currentTakeSum += stoneValue[i + k];
          dp[i] = max(dp[i], currentTakeSum - dp[i + k + 1]);
        }
      }
    }

    if (dp[0] > 0) return "Alice";
    if (dp[0] < 0) return "Bob";
    return "Tie";
  }
};

int main() {
  int n, x;
  vector<int> inp;
  Solution sol;
  cin >> n;
  while (n--) {
    cin >> x;
    inp.emplace_back(x);
  }
  cout << sol.stoneGameIII(inp) << endl;
  return 0;
}