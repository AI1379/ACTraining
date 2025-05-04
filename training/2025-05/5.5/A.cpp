#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pll pair<ll, ll>
int from_hex(char c) {
  if (c >= '0' && c <= '9')
    return c - '0';
  if (c >= 'A' && c <= 'F')
    return c - 'A' + 10;
  if (c >= 'a' && c <= 'f')
    return c - 'a' + 10;
  return -1;
}
int main() {
  int tmp;
  string in, out;
  ios::sync_with_stdio(false);
  cin >> tmp >> in;
  for (unsigned i = 0; i < in.length(); i += 2) {
    int x = (from_hex(in[i]) * 16 + from_hex(in[i + 1]));
    out.push_back(x ^ tmp);
    tmp = x;
  }
  cout << out << endl;
  return 0;
}