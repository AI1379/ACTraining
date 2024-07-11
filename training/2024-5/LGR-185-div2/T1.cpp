#include <algorithm>
#include <iostream>
using namespace std;
#define ll long long
const ll MAXN = 1000010;
ll n;
ll w[MAXN];
int main() {
  ios::sync_with_stdio(false);
  cin >> n;
  for (auto i = 1; i <= n; ++i) {
    cin >> w[i];
  }
  sort(w + 1, w + n + 1);
  for (int i = 1, j = n; i < j; ++i, --j)
    cout << w[j] << ' ' << w[i] << ' ';
  cout << w[n / 2 + 1] << endl;
  for (int i = 1, j = n; i < j; ++i, --j)
    cout << w[i] << ' ' << w[j] << ' ';
  cout << w[n / 2 + 1] << endl;
  return 0;
}