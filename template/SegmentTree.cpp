#include <bits/stdc++.h>
using namespace std;
template <typename Value, typename Tag, size_t Size, typename PushdownFunc,
          typename PushupFunc>
class SegmentTree {
public:
  using PushupType = std::function<void(Value &, Value &, Value &)>;
  using PushdownType = std::function<void(size_t, Value &, Tag &, Value &,
                                          Tag &, Value &, Tag &)>;
  using BuildType = std::function<void(size_t, Value &, Tag &)>;
  using MergeType = std::function<Value(const Value &, const Value &)>;
  using ModifyType = PushdownType;
  using BreakType = std::function<bool(const Value &)>;
  using TagType = std::function<bool(const Value &)>;

  struct TrueFunctor {
    template <typename... Args> bool operator()(Args...) { return true; }
  };
  struct FalseFunctor {
    template <typename... Args> bool operator()(Args...) { return false; }
  };

  template <typename BuildFunc> void build(size_t n) {
    this->buildImpl<BuildFunc>(1, 1, n);
  }
  template <typename MergeFunc, typename... Args>
  Value query(size_t l, size_t r, Args &&...args) {
    return this->queryImpl<MergeFunc>(1, l, r, std::forward<Args>(args)...);
  }
  template <typename ModifyFunc, typename BreakFunc = FalseFunctor,
            typename TagFunc = TrueFunctor, typename... Args>
  void modify(size_t l, size_t r, Args &&...args) {
    this->modifyImpl<ModifyFunc, BreakFunc, TagFunc>(
        1, l, r, std::forward<Args>(args)...);
  }

private:
  struct Node {
    size_t l, r, mid, len;
    Value value;
    Tag tag;
  };
  Node data_[Size * 4];

  template <typename BuildFunc> void buildImpl(size_t cur, size_t l, size_t r) {
    data_[cur].l = l;
    data_[cur].r = r;
    data_[cur].mid = (l + r) / 2;
    data_[cur].len = (r - l + 1);
    if (l == r) {
      BuildFunc{}(l, data_[cur].value, data_[cur].tag);
      return;
    }
    buildImpl<BuildFunc>(cur * 2, l, data_[cur].mid);
    buildImpl<BuildFunc>(cur * 2 + 1, data_[cur].mid + 1, r);
    PushupFunc{}(data_[cur].len, data_[cur].value, data_[cur * 2].value,
                 data_[cur * 2 + 1].value);
  }
  template <typename MergeFunc, typename... Args>
  Value queryImpl(size_t cur, size_t l, size_t r, Args &&...args) {
    if (l <= data_[cur].l && data_[cur].r <= r) {
      return data_[cur].value;
    }
    PushdownFunc{}(data_[cur].len, data_[cur].value, data_[cur].tag,
                   data_[cur * 2].value, data_[cur * 2].tag,
                   data_[cur * 2 + 1].value, data_[cur * 2 + 1].tag);
    Value res = MergeFunc::init;
    if (l <= data_[cur].mid)
      res = MergeFunc{}(res, queryImpl<MergeFunc>(cur * 2, l, r,
                                                  std::forward<Args>(args)...));
    if (data_[cur].mid + 1 <= r)
      res = MergeFunc{}(res, queryImpl<MergeFunc>(cur * 2 + 1, l, r,
                                                  std::forward<Args>(args)...));
    return res;
  }
  template <typename ModifyFunc, typename BreakFunc, typename TagFunc,
            typename... Args>
  void modifyImpl(size_t cur, size_t l, size_t r, Args &&...args) {
    if (BreakFunc{}(data_[cur].len, data_[cur].value, data_[cur].tag,
                    std::forward<Args>(args)...))
      return;
    if (l <= data_[cur].l && data_[cur].r <= r &&
        TagFunc{}(data_[cur].len, data_[cur].value, data_[cur].tag,
                  std::forward<Args>(args)...)) {
      ModifyFunc{}(data_[cur].len, data_[cur].value, data_[cur].tag,
                   std::forward<Args>(args)...);
      return;
    }
    PushdownFunc{}(data_[cur].len, data_[cur].value, data_[cur].tag,
                   data_[cur * 2].value, data_[cur * 2].tag,
                   data_[cur * 2 + 1].value, data_[cur * 2 + 1].tag);
    if (l <= data_[cur].mid)
      modifyImpl<ModifyFunc, BreakFunc, TagFunc>(cur * 2, l, r,
                                                 std::forward<Args>(args)...);
    if (data_[cur].mid + 1 <= r)
      modifyImpl<ModifyFunc, BreakFunc, TagFunc>(cur * 2 + 1, l, r,
                                                 std::forward<Args>(args)...);
    PushupFunc{}(data_[cur].len, data_[cur].value, data_[cur * 2].value,
                 data_[cur * 2 + 1].value);
  }
};

#define ll long long
const ll MAXN = 500010;
const ll INF = (1ll << 60);
ll n, m;
ll a[MAXN];

struct Value {
  ll sum, cmax, hmax, cnt, secmax;
};
struct Tag {
  ll tag, maxtag, tag2, maxtag2;
};

struct PushdownFunc {
  void update(size_t len, Value &v, Tag &t, Tag dtag) {
    auto tag = dtag.tag, tag2 = dtag.tag2, maxtag = dtag.maxtag,
         maxtag2 = dtag.maxtag2;
    v.hmax = max(v.hmax, v.cmax + maxtag2);
    v.cmax += tag2;
    v.sum += tag * (len - v.cnt) + tag2 * v.cnt;
    if (v.secmax != -INF)
      v.secmax += tag;
    t.maxtag = max(t.maxtag, t.tag + maxtag);
    t.maxtag2 = max(t.maxtag2, t.tag2 + maxtag2);
    t.tag += tag;
    t.tag2 += tag2;
  }
  void operator()(size_t len, Value &, Tag &ct, Value &lv, Tag &lt, Value &rv,
                  Tag &rt) {
    auto cmax = max(lv.cmax, rv.cmax);
    auto mtag = ct;
    mtag.maxtag2 = mtag.maxtag;
    mtag.tag2 = mtag.tag;
    if (lv.cmax == cmax)
      update(len, lv, lt, ct);
    else
      update(len, lv, lt, mtag);
    if (rv.cmax == cmax)
      update(len, rv, rt, ct);
    else
      update(len, rv, rt, mtag);
    ct.tag = ct.tag2 = ct.maxtag = ct.maxtag2 = 0;
  }
};
struct PushupFunc {
  void operator()(size_t, Value &cv, const Value &lv, const Value &rv) {
    cv.sum = lv.sum + rv.sum;
    cv.cmax = max(lv.cmax, rv.cmax);
    cv.hmax = max(lv.hmax, rv.hmax);
    cv.secmax = max(lv.cmax == rv.cmax ? -INF : min(lv.cmax, rv.cmax),
                    max(lv.secmax, rv.secmax));
    cv.cnt = 0;
    if (lv.cmax == cv.cmax)
      cv.cnt += lv.cnt;
    if (rv.cmax == cv.cmax)
      cv.cnt += rv.cnt;
  }
};

struct BuildFunc {
  void operator()(size_t p, Value &v, Tag &) {
    v.sum = v.cmax = v.hmax = a[p];
    v.secmax = -INF;
    v.cnt = 1;
  }
};
struct MergeSumFunc {
  static constexpr const Value init = {0, 0, 0, 0, 0};
  Value operator()(const Value &l, const Value &r) {
    return {l.sum + r.sum, 0, 0, 0, 0};
  }
};
struct MergeMaxFunc {
  static constexpr const Value init = {0, -INF, 0, 0, 0};
  Value operator()(const Value &l, const Value &r) {
    return {0, max(l.cmax, r.cmax), 0, 0, 0};
  }
};
struct MergeHMaxFunc {
  static constexpr const Value init = {0, 0, -INF, 0, 0};
  Value operator()(const Value &l, const Value &r) {
    return {0, 0, max(l.hmax, r.hmax), 0, 0};
  }
};

struct ModifySumFunc {
  void operator()(size_t len, Value &cv, Tag &ct, ll k) {
    ct.tag += k;
    ct.maxtag = max(ct.maxtag, ct.tag);
    ct.tag2 += k;
    ct.maxtag2 = max(ct.maxtag2, ct.tag2);
    cv.sum += k * len;
    cv.cmax += k;
    cv.hmax = max(cv.hmax, cv.cmax);
    if (cv.secmax != -INF)
      cv.secmax += k;
  }
};
struct MinBreakFunc {
  bool operator()(size_t, const Value &val, const Tag &, ll v) {
    return val.cmax <= v;
  }
};
struct MinTagFunc {
  bool operator()(size_t, const Value &val, const Tag &, ll v) {
    return val.secmax < v;
  }
};
struct ModifyMinFunc {
  void operator()(size_t, Value &val, Tag &tag, ll v) {
    auto d = val.cmax - v;
    val.cmax = v;
    val.sum -= d * val.cnt;
    tag.tag2 -= d;
  }
};

SegmentTree<Value, Tag, MAXN, PushdownFunc, PushupFunc> segt;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  ll op, l, r, v;
  cin >> n >> m;
  for (int i = 1; i <= n; ++i)
    cin >> a[i];
  segt.build<BuildFunc>(n);
  while (m--) {
    cin >> op >> l >> r;
    if (op == 1) {
      cin >> v;
      segt.modify<ModifySumFunc>(l, r, v);
    } else if (op == 2) {
      cin >> v;
      segt.modify<ModifyMinFunc, MinBreakFunc, MinTagFunc>(l, r, v);
    } else if (op == 3) {
      cout << segt.query<MergeSumFunc>(l, r).sum << '\n';
    } else if (op == 4) {
      cout << segt.query<MergeMaxFunc>(l, r).cmax << '\n';
    } else if (op == 5) {
      cout << segt.query<MergeHMaxFunc>(l, r).hmax << '\n';
    }
  }
  return 0;
}