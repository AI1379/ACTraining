#include <cstdio>
#define ll long long
const ll MAXN = 31;
ll n;
ll val[MAXN];
bool vis[MAXN];
bool check(ll x) {
  for (ll i = 2; i * i <= x; i++) {
    if (x % i == 0)
      return false;
  }
  return true;
}
void dfs2(int dep) {
  if (dep == n + 1) {
    for (int i = 1; i <= n; ++i) {
      if (!check(val[i] + val[(i + 1) % n]))
        return;
    }
    for (int i = 1; i <= n; ++i) {
      printf("%lld ", val[i]);
    }
    printf("\n");
    return;
  }
  for (int i = 1; i <= n; ++i) {
    if (i > 1 && dep == 1)
      break;
    if (vis[i])
      continue;
    val[dep] = i;
    vis[i] = true;
    dfs2(dep + 1);
    vis[i] = false;
  }
}
void dfs(int dep) {
  if (dep == n + 1) {
    if (check(val[1] + val[n])) {
      for (int i = 1; i <= n; ++i) {
        printf("%lld ", val[i]);
      }
      printf("\n");
    }
    return;
  }
  for (int i = 1; i <= n; ++i) {
    if (i > 1 && dep == 1)
      break;
    if (vis[i] || (dep > 1 && !check(val[dep - 1] + i)))
      continue;
    val[dep] = i;
    vis[i] = true;
    dfs(dep + 1);
    vis[i] = false;
  }
}
int main() {
  scanf("%lld", &n);
  dfs(1);
  return 0;
}