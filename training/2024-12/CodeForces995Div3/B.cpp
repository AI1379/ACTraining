#include <bits/stdc++.h>
using namespace std;
#define ll long long
ll test_cases;
ll n, a, b, c;
ll r, remain;
void solve() {
  cin >> n >> a >> b >> c;
  r = n / (a + b + c);
  remain = n % (a + b + c);
  if (remain == 0) {
    cout << r * 3 << endl;
  } else if (remain <= a) {
    cout << r * 3 + 1 << endl;
  } else if (remain <= a + b) {
    cout << r * 3 + 2 << endl;
  } else {
    cout << r * 3 + 3 << endl;
  }
}
int main() {
  ios::sync_with_stdio(false);
  cin >> test_cases;
  while (test_cases--) {
    solve();
  }
  return 0;
}
/*
4
12 1 5 3
6 6 7 4
16 3 4 1
1000000000 1 1 1

5
1
6
1000000000

*/