#include <algorithm>
#include <iostream>
#include <memory>
#include <queue>
#include <stdexcept>
#include <utility>
#include <vector>

#ifdef DEBUG
#define DOUT std::cout
#else
#define DOUT                                                                   \
  if constexpr (false)                                                         \
  std::cout
#endif

// using Value = int;
// constexpr int Order = 3;
template <typename Value, int Order = 3> class BPlusTree {
private:
  struct Node {
    bool leaf;
    std::vector<Value> keys;
    std::vector<std::unique_ptr<Node>> children;
    Node *parent;
    Node(bool lf, Node *p) : leaf(lf), parent(p) {}
  };

  static constexpr int MaxKeys = Order;
  static constexpr int Mid = MaxKeys / 2 + 1;

  std::unique_ptr<Node> root_ = nullptr;

  Node *find_leaf(const Value &x) {
    Node *cur = root_.get();
    while (!cur->leaf)
      cur = cur->children[std::upper_bound(cur->keys.begin(), cur->keys.end(),
                                           x) -
                          cur->keys.begin()]
                .get();
    return cur;
  }

  void attach(Node *node, const Value &sep, std::unique_ptr<Node> right) {
    Node *par = node->parent;
    if (!par) {
      auto new_root = std::make_unique<Node>(false, nullptr);
      new_root->keys.push_back(sep);
      new_root->children.push_back(std::move(root_));
      new_root->children.push_back(std::move(right));
      new_root->children[0]->parent = new_root.get();
      new_root->children[1]->parent = new_root.get();
      root_ = std::move(new_root);
      return;
    }

    auto pos = child_idx(par, node);
    par->keys.insert(par->keys.begin() + pos, sep);
    right->parent = par;
    par->children.insert(par->children.begin() + pos + 1, std::move(right));

    if ((int)par->keys.size() == Order) {
      // internal nodes hold at most Order-1 keys; overflow -> 1 + 1, mid up
      auto up = std::make_unique<Node>(false, par->parent);
      Value sep_up = std::move(par->keys[1]);
      up->keys.push_back(std::move(par->keys[2]));
      par->keys.resize(1);
      up->children.reserve(Order);
      for (auto it = par->children.begin() + 2; it != par->children.end();
           ++it) {
        (*it)->parent = up.get();
        up->children.push_back(std::move(*it));
      }
      par->children.resize(2);
      attach(par, sep_up, std::move(up));
    }
  }

  int child_idx(Node *par, Node *node) {
    for (size_t i = 0; i < par->children.size(); ++i)
      if (par->children[i].get() == node)
        return (int)i;
    throw std::invalid_argument("Node should be a child of parent");
  }

  void split(Node *node) {
    auto right = std::make_unique<Node>(true, node->parent);
    Value sep = node->keys[Mid];
    right->keys.assign(std::make_move_iterator(node->keys.begin()) + Mid,
                       std::make_move_iterator(node->keys.end()));
    node->keys.resize(Mid);

    attach(node, sep, std::move(right));
  }

public:
  bool insert(const Value &x) {
    if (!root_) {
      root_ = std::make_unique<Node>(true, nullptr);
      root_->keys.push_back(x);
      return true;
    }

    Node *leaf = find_leaf(x);
    auto it = std::lower_bound(leaf->keys.begin(), leaf->keys.end(), x);
    if (it != leaf->keys.end() && *it == x)
      return false;

    leaf->keys.insert(it, x);
    DOUT << x << " inserted" << std::endl;
    if ((int)leaf->keys.size() > MaxKeys)
      split(leaf);
    return true;
  }

  bool search(const Value &x) {
    if (!root_)
      return false;
    Node *node = find_leaf(x);
    return std::binary_search(node->keys.begin(), node->keys.end(), x);
  }

  friend std::ostream &operator<<(std::ostream &os, const BPlusTree &t) {
    if (!t.root_)
      return os;
    std::queue<const Node *> q;
    q.push(t.root_.get());
    while (!q.empty()) {
      int sz = q.size();
      while (sz--) {
        auto *node = q.front();
        q.pop();
        os << '[';
        for (size_t i = 0; i < node->keys.size(); ++i) {
          if (i)
            os << ',';
          os << node->keys[i];
        }
        os << ']';
        for (auto &c : node->children)
          q.push(c.get());
      }
      os << '\n';
    }
    return os;
  }
};

int main() {
  int n, x;
  BPlusTree<int> tree;
  std::cin >> n;
  while (n--) {
    std::cin >> x;
    if (!tree.insert(x))
      std::cout << "Key " << x << " is duplicated" << std::endl;
  }
  std::cout << tree;
  return 0;
}
