#include <bits/stdc++.h>
using namespace std;
#define ll long long
const ll MAXN = 63;
ll n, l;
ll cnt = 0;
char ans[MAXN];
bool check(ll pos) {
  bool flag;
  for (int len = 1; len <= pos / 2; ++len) {
    flag = true;
    for (int i = 0; i < len; ++i) {
      if (ans[pos - i] != ans[pos - len - i]) {
        flag = false;
        break;
      }
    }
    if (flag)
      return true;
  }
  return false;
}
void dfs(ll pos) {
  for (int i = 0; i < l; ++i) {
    ans[pos] = 'A' + i;
    if (!check(pos)) {
      ++cnt;
      if (cnt == n) {
        for (int j = 1; j <= pos; ++j) {
          cout << ans[j];
        }
        cout << endl;
        exit(0);
      }
      dfs(pos + 1);
    }
  }
}
int main() {
  ios::sync_with_stdio(false);
  cin >> n >> l;
  dfs(1);
  return 0;
}