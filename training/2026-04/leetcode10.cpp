#include <bits/stdc++.h>

using namespace std;

#ifdef DEBUG
#define DOUT cerr
#else
#define DOUT \
  if constexpr (false) cerr
#endif

class Solution {
 public:
  bool isMatch(string s, string p) {
    auto cs = s.begin(), cp = p.begin();
    char current_state;
    bool star = false;
    while (cs < s.end() && cp < p.end()) {
      current_state = *cp;
      if (cp < p.end() - 1)
        star = (*(cp + 1) == '*');
      else
        star = false;
      DOUT << *cs << ' ' << *cp << ' ' << boolalpha << star << endl;
      if (star) {
        while (cs < s.end() && (*cs == current_state || current_state == '.'))
          ++cs;
        cp += 2;
        while (cp < p.end() && (*cp == current_state || *cp == '.'))
          ++cp;
      } else {
        if (*cs != current_state && current_state != '.') break;
        ++cs;
        ++cp;
      }
    }
    while (cp + 1 < p.end() && *(cp + 1) == '*') cp += 2;
    return cs == s.end() && cp == p.end();
  }
};

int main() {
  string s, p;
  cin >> s >> p;
  Solution sol{};
  cout << boolalpha << sol.isMatch(s, p) << endl;
  return 0;
}