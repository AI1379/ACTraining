#include <bits/stdc++.h>
using namespace std;
#define ll long long
const ll MAXN = 100010;
ll t;
ll n;
string s1, s2, t1, t2;
ll s10, s11, s20, s21;
ll ans = 0;
void solve() {
  ll a, b;
  cin >> n;
  cin >> s1 >> s2 >> t1 >> t2;
  ans = s10 = s11 = s20 = s21 = 0;
  for (int i = 0; i < n; i++) {
    if (t1[i] == '1') {
      if (s1[i] == '0')
        s10++;
      else
        s11++;
    }
    if (t2[i] == '1') {
      if (s2[i] == '0')
        s20++;
      else
        s21++;
    }
  }
  cout << s10 << ' ' << s11 << ' ' << s20 << ' ' << s21 << '\n';
  a = b = 0;
  for (int i = 0; i < n; ++i) {
    if (s1[i] == '0' && t1[i] == '0')
      ++a;
    else if (s1[i] == '1' && t1[i] == '0')
      ++b;
  }
  ans += min(a, s20) + min(b, s21);
  s20 = max(0ll, s20 - a);
  s21 = max(0ll, s21 - b);
  cout << a << b << s20 << s21 << endl;
  a = b = 0;
  for (int i = 0; i < n; ++i) {
    if (s2[i] == '0' && t2[i] == '0')
      ++a;
    else if (s2[i] == '1' && t2[i] == '0')
      ++b;
  }
  ans += min(a, s10) + min(b, s11);
  s10 = max(0ll, s10 - a);
  s11 = max(0ll, s11 - b);
  ans += min(s10, s20) + min(s11, s21);
  cout << a << b << s10 << s11 << endl;
  cout << ans << '\n';
}
int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  cin >> t;
  while (t--) {
    solve();
  }
  return 0;
}