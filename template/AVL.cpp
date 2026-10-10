#include <algorithm>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <type_traits>
#include <utility>

#ifdef DEBUG
#define DOUT std::cout
#else
#define DOUT                                                                   \
  if constexpr (false)                                                         \
  std::cout
#endif

// using Value = int;
template <typename Value> class AVLTree {
private:
  struct Node {
    Value value;
    std::unique_ptr<Node> l_ptr, r_ptr;
    Node *parent;
    int h;
  };
  bool is_left(Node *ptr) {
    if (!ptr || !ptr->parent)
      throw std::invalid_argument("Node should not be root or nullptr");
    return ptr->parent->l_ptr.get() == ptr;
  }
  bool is_right(Node *ptr) {
    if (!ptr || !ptr->parent)
      throw std::invalid_argument("Node should not be root or nullptr");
    return ptr->parent->r_ptr.get() == ptr;
  }

  // h and bf
  static auto h(const auto &ptr) { return ptr ? ptr->h : 0; }
  static auto bf(const auto &ptr) {
    auto lh = h(ptr->l_ptr);
    auto rh = h(ptr->r_ptr);
    return lh - rh;
  }
  static auto update_h(auto &ptr) {
    ptr->h = std::max(h(ptr->l_ptr), h(ptr->r_ptr)) + 1;
  }

  // owner helper
  std::unique_ptr<Node> &owner(Node *ptr) {
    if (!ptr->parent)
      return root_;
    if (is_left(ptr))
      return ptr->parent->l_ptr;
    else if (is_right(ptr))
      return ptr->parent->r_ptr;
    throw std::invalid_argument("Node should be part of the tree");
  }

  auto rotate_right(Node *ptr) {
    if (!ptr)
      throw std::invalid_argument("Node should not be empty");
    if (!ptr->l_ptr)
      throw std::invalid_argument("Node should have a l_ptr");
    auto par = ptr->parent;
    auto lson = ptr->l_ptr.get();

    auto &self_owner = owner(ptr);
    auto &lson_owner = ptr->l_ptr;

    auto old_self = std::move(self_owner);

    lson->parent = par;
    self_owner = std::move(lson_owner);

    if (lson->r_ptr)
      lson->r_ptr->parent = ptr;
    ptr->l_ptr = std::move(lson->r_ptr);

    ptr->parent = lson;
    lson->r_ptr = std::move(old_self);

    // Update h
    update_h(ptr);
    update_h(lson);

    return lson;
  }

  auto rotate_left(Node *ptr) {
    if (!ptr)
      throw std::invalid_argument("Node should not be empty");
    if (!ptr->r_ptr)
      throw std::invalid_argument("Node should have a r_ptr");
    auto par = ptr->parent;
    auto rson = ptr->r_ptr.get();

    auto &self_owner = owner(ptr);
    auto &rson_owner = ptr->r_ptr;

    auto old_self = std::move(self_owner);

    rson->parent = par;
    self_owner = std::move(rson_owner);

    if (rson->l_ptr)
      rson->l_ptr->parent = ptr;
    ptr->r_ptr = std::move(rson->l_ptr);

    ptr->parent = rson;
    rson->l_ptr = std::move(old_self);

    // Update h
    update_h(ptr);
    update_h(rson);

    return rson;
  }

  auto rebalance(Node *ptr) {
    update_h(ptr);
    auto balance = bf(ptr);

    if (balance > 1) {
      if (bf(ptr->l_ptr) >= 0) {
        DOUT << "LL" << std::endl;
        ptr = rotate_right(ptr);
      } else {
        DOUT << "LR" << std::endl;
        rotate_left(ptr->l_ptr.get());
        ptr = rotate_right(ptr);
      }
    } else if (balance < -1) {
      if (bf(ptr->r_ptr) <= 0) {
        DOUT << "RR" << std::endl;
        ptr = rotate_left(ptr);
      } else {
        DOUT << "RL" << std::endl;
        rotate_right(ptr->r_ptr.get());
        ptr = rotate_left(ptr);
      }
    }

    return ptr;
  }

public:
  void insert(const Value &x) {
    // Find proper position
    Node *current = root_.get();
    Node *pre = nullptr;
    auto *owner = &root_;

    while (current) {
      pre = current;

      if (current->value <= x) {
        owner = &current->r_ptr;
        current = current->r_ptr.get();
      } else {
        owner = &current->l_ptr;
        current = current->l_ptr.get();
      }
    }

    *owner = std::make_unique<Node>(std::move(x), nullptr, nullptr, pre, 1);
    current = owner->get();

    while (current != root_.get()) {
      DOUT << current->value << ' ' << current->h << std::endl;
      current = rebalance(current);
      current = current->parent;
    }
    DOUT << current->value << ' ' << current->h << std::endl;
    current = rebalance(current);
  }

  auto get_root() { return root_->value; }

private:
  std::unique_ptr<Node> root_ = nullptr;
};

int main() {
  int n, x;
  AVLTree<int> tree;
  std::cin >> n;
  while (n--) {
    std::cin >> x;
    tree.insert(x);
    DOUT << x << " inserted" << std::endl;
  }
  std::cout << tree.get_root() << std::endl;
  return 0;
}