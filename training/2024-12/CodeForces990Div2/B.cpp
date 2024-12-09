#include <bits/stdc++.h>
using namespace std;
#define ll long long
ll t;
ll table[256];
ll pos[256];
ll n;
char s[100010];
char mn, mx;
void solve() {
  memset(pos, 0, sizeof(pos));
  memset(table, 0, sizeof(table));
  memset(s, 0, sizeof(s));
  scanf("%lld", &n);
  scanf("%s", s + 1);
  mn = mx = s[1];
  for (int i = 1; i <= n; ++i) {
    table[s[i]]++;
    pos[s[i]] = i;
  }
  for (int i = 1; i <= n; ++i) {
    if (table[s[i]] > table[mx] || (table[s[i]] == table[mx] && s[i] > mx))
      mx = s[i];
    if (table[s[i]] < table[mn] || (table[s[i]] == table[mn] && s[i] < mn))
      mn = s[i];
    // printf("%c %lld %c %lld\n", mx, table[mx], mn, table[mn]);
  }
  s[pos[mn]] = mx;
  printf("%s\n", s + 1);
}
int main() {
  scanf("%lld", &t);
  while (t--)
    solve();
  return 0;
}
/*
6
3
abc
4
xyyx
8
alphabet
1
k
10
aabbccddee
6
ttbddq

*/