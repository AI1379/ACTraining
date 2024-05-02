#include <cstddef>
#include <iostream>
#include <random>
#include <vector>
using namespace std;
#define ll long long
ll t;
template <typename BaseType, typename PowType>
inline BaseType power(BaseType base, PowType pow, const BaseType &mod) {
  BaseType res{1};
  while (pow > PowType(0)) {
    if (pow % 2 == PowType(1))
      res = res * base % mod;
    base = base * base % mod;
    pow = pow / 2;
  }
  return res;
}
inline bool probablePrime(const ll &n) {
  constexpr const size_t certainty = 4;
  static std::random_device rd;
  static std::mt19937_64 rng(rd());
  static std::uniform_int_distribution<ll> dist(2, n - 1);
  if (n < 3 || n % 2 == 0)
    return n == 2;
  ll u = n - 1;
  uint64_t t = 0;
  while (u % 2 == 0) {
    u = u / 2;
    ++t;
  }
  for (size_t i = 0; i < certainty; ++i) {
    auto base = dist(rng);
    auto v = power(base, u, n);
    if (v == 1)
      continue;
    uint64_t s = 0;
    for (s = 0; s < t; ++s) {
      if (v == n - 1)
        break;
      v = v * v % n;
    }
    if (s == t)
      return false;
  }
  return true;
}
void solve() {
  ll n, m, cur, x = 1;
  cin >> n >> m;
  cur = n;
  for (int i = 2; cur > 1; ++i) {
    if (cur % i == 0) {
      x *= i;
      while (cur % i == 0)
        cur /= i;
    }
    if (n > (1 << 30))
      if (probablePrime(cur)) {
        x *= cur;
        break;
      }
  }
  cur = m / x;
  cout << cur + 1 << endl;
  return;
}
int main() {
  ios::sync_with_stdio(false);
  cin >> t;
  while (t--)
    solve();
  return 0;
}