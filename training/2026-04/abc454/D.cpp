#include <bits/stdc++.h>
using namespace std;

#ifdef DEBUG
#define DOUT cout
#else
#define DOUT \
  if constexpr (false) cerr
#endif

#define ll long long

string simplify(const string& s) {
  string res;
  for (auto i = 0ull; i < s.length(); ++i) {
    if (s[i] == '(') {
      res.push_back('(');
    } else if (s[i] == 'x') {
      if (i < s.length() - 1 && s[i + 1] == 'x') {
        i += 2;
        while (i < s.length() && s[i] == ')' && res.back() == '(') {
          res.pop_back();
          ++i;
        }
        res += "xx";
        --i;  // i-- because of the for loop
      } else {
        res += 'x';
      }
    } else {
      res.push_back(')');
    }
  }
  return res;
}

void solve() {
  string a, b;
  cin >> a >> b;
  string as = simplify(a);
  string bs = simplify(b);
  DOUT << "as: " << as << endl;
  DOUT << "bs: " << bs << endl;
  if (as == bs) {
    cout << "Yes\n";
  } else {
    cout << "No\n";
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int t;
  cin >> t;
  while (t--) {
    solve();
  }
  return 0;
}

/*
6
(xx)x
x(xx)
(x)x
(xx)
)x()x(
)x()x(
x
(x)
(((((xx)))))x
x((((((((((xx))))))))))
((xx)xx)xx
(x((xx))x)(xx)
*/
