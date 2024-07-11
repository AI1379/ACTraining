#include <bits/stdc++.h>
using namespace std;
#define ll long long
const ll MAXN = 1000010;
ll n;
ll x[MAXN], p[MAXN], c[MAXN];
ll dp[MAXN];
int main() {
  ios::sync_with_stdio(false);
  cin >> n;
  for (int i = 1; i <= n; ++i) {
    cin >> x[i] >> p[i] >> c[i];
  }
  return 0;
}