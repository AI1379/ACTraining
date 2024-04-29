#include <cstdio>
#include <iostream>
#include <map>
#include <string>
#include <utility>
#define ll long long
#define check(x, y) (0 < (x) && (x) <= n && 0 < (y) && (y) <= m)
using namespace std;
const ll MAXN = 63;
const ll dx[] = {1, 0, -1, 0, -1, 1, 1, -1};
const ll dy[] = {0, 1, 0, -1, 1, -1, 1, -1};
ll n, m;
char mp[MAXN][MAXN];
map<pair<char, char>, ll> tab;
int main() {
  scanf("%lld%lld", &n, &m);
  for (auto i = 1; i <= n; ++i) {
    scanf("%s", mp[i] + 1);
  }
  for (auto k = 0; k < 8; ++k) {
    for (auto i1 = 1; i1 <= n; ++i1) {
      for (auto j1 = 1; j1 <= m; ++j1) {
        auto i2 = i1 + dx[k], j2 = j1 + dy[k];
        auto i3 = i2 + dx[k], j3 = j2 + dy[k];
        auto i4 = i3 + dx[k], j4 = j3 + dy[k];
        if (check(i1, j1) && check(i2, j2) && check(i3, j3)) {
          if (mp[i2][j2] == mp[i3][j3] && mp[i1][j1] != mp[i2][j2] &&
              mp[i1][j1] != 'M' && mp[i2][j2] != 'O') {
            ++tab[{mp[i1][j1], mp[i2][j2]}];
          }
        }
      }
    }
  }
  ll ans = 0;
  for (auto &p : tab) {
    ans = max(ans, p.second);
  }
  printf("%lld\n", ans);
  return 0;
}