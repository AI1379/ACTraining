#include <bits/stdc++.h>
using namespace std;
#define pii pair<int, int>

class Solution {
 public:
  pii stack[20010];
  int top = 0;
  int trap(vector<int>& height) {
    int ans = 0;
    bool first = true;
    for (size_t i = 0; i < height.size(); ++i) {
      // cout << "i: " << i << " height: " << height[i] << ' ' << ans << endl;
      if (first && i < height.size() - 1 && height[i] < height[i + 1])
        continue;
      else
        first = false;
      while (top && stack[top].first <= height[i]) --top;
      stack[++top] = {height[i], i};
      ans += stack[1].first - height[i];
    }
    for (size_t i = 1; i < top; ++i) {
      ans -= (stack[i].first - stack[i + 1].first) *
             (height.size() - stack[i].second - 1);
    }
    return ans;
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
  cout << sol.trap(inp) << endl;
  return 0;
}