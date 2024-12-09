#include <bits/stdc++.h>
#include <queue>
using namespace std;
#define ll long long
#define pll pair<ll, ll>
const ll MAXN = 100010;
ll t;
ll n;
ll val[MAXN];
ll ans[MAXN];
void solve() {
  priority_queue<pll, vector<pll>, greater<pll>> pq1;
  priority_queue<ll, vector<ll>, greater<ll>> pq2;
  cin >> n;
  for (int i = 1; i <= n; ++i) {
    cin >> val[i];
    pq1.push({val[i], i});
  }
  int idx = 1, cur = 0;
  while (!pq1.empty()) {
    while (!pq1.empty() && pq1.top().second < idx)
      pq1.pop();
    if (pq1.empty())
      break;
    auto [v, id] = pq1.top();
    if (!pq2.empty() && pq2.top() < v) {
      while (idx <= n)
        pq2.push(val[idx++] + 1);
      idx = n + 1;
      break;
    }
    pq1.pop();
    while (idx < id)
      pq2.push(val[idx++] + 1);
    ans[++cur] = v;
    idx++;
  }
  while (!pq2.empty()) {
    ans[++cur] = pq2.top();
    pq2.pop();
  }
  for (int i = 1; i <= n; ++i) {
    cout << ans[i] << " ";
  }
  cout << endl;
}
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cin >> t;
  while (t--) {
    solve();
  }
  return 0;
}