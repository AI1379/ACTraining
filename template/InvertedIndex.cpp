#include <algorithm>
#include <cctype>
#include <cmath>
#include <format>
#include <iostream>
#include <ranges>
#include <string>
#include <unordered_map>

using namespace std;
#define ll long long
#define ull unsigned long long

#ifdef DEBUG
#define DOUT std::cout
#else
#define DOUT                                                                   \
  if constexpr (false)                                                         \
  std::cout
#endif

struct Article {
  string title;
  string content;
};

using FreqMap = unordered_map<string, ull>;

unordered_map<string, FreqMap> inverted_index;
unordered_map<string, double> cached_norms;

Article read_article() {
  Article res;
  cin >> res.title;
  string buf;
  while (getline(cin, buf)) {
    while (!buf.empty() && buf.back() == '\r')
      buf.pop_back();
    if (buf == "#")
      break;
    res.content += buf;
    res.content += '\n';
  }
  return res;
}

auto stem(string w) {
  if (w.size() > 3 && w.ends_with("ies"))
    w = w.substr(0, w.size() - 3) + "y";
  else if (w.size() > 3 && (w.ends_with("es") || w.ends_with("ed")))
    w.resize(w.size() - 2);
  else if (w.size() > 3 && w.ends_with("ing"))
    w.resize(w.size() - 3);
  return w;
}

void build_index(Article article) {
  inverted_index.insert({article.title, FreqMap{}});

  auto &idx = inverted_index[article.title];

  auto words =
      article.content | views::transform([](char c) {
        return ::isalnum(static_cast<unsigned char>(c)) ? c : ' ';
      }) |
      views::split(' ') |
      views::filter([](auto &&rng) { return !ranges::empty(rng); }) |
      views::transform([](auto &&rng) {
        string w;
        for (char c : rng)
          w += static_cast<char>(::tolower(static_cast<unsigned char>(c)));
        return w;
      }) |
      views::transform(stem);

#ifdef DEBUG
  for (const auto &w : words)
    DOUT << w << ' ';
  DOUT << '\n';
#endif

  for (auto word : words) {
    if (!idx.contains(word))
      idx[word] = 1;
    else
      ++idx[word];
  }

  double n2 = 0;
  for (const auto &[w, c] : idx)
    n2 += 1.0 * c * c;
  cached_norms[article.title] = n2;
}

double calculate(const string &title_a, const string &title_b) {
  auto &idx_a = inverted_index[title_a];
  auto &idx_b = inverted_index[title_b];

  double norm_a = cached_norms[title_a];
  double norm_b = cached_norms[title_b];

  auto &small = idx_a.size() <= idx_b.size() ? idx_a : idx_b;
  auto &large = &small == &idx_a ? idx_b : idx_a;
  double proj = 0;
  for (const auto &[w, c] : small)
    if (auto it = large.find(w); it != large.end())
      proj += 1.0 * c * it->second;

  DOUT << format("{} {} {}", norm_a, norm_b, proj) << '\n';

  double denom = sqrt(norm_a) * sqrt(norm_b);
  double cosv = denom > 0 ? proj / denom : 0.0;
  cosv = clamp(cosv, -1.0, 1.0);
  return acos(cosv);
}

int main() {
  int n, m;
  string s, t;
  cin >> n;
  while (n--) {
    build_index(read_article());
  }
  cin >> m;
  for (auto idx : views::iota(1, m + 1)) {
    cin >> s >> t;
    auto res = calculate(s, t);
    cout << format("Case {}: {:.3f}\n", idx, res);
  }
  return 0;
}
