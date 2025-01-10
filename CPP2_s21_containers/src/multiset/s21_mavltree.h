#ifndef CPP2_S21_CONTAINERS_2_SRC_MULTISET_S21_MAVLTREE_H
#define CPP2_S21_CONTAINERS_2_SRC_MULTISET_S21_MAVLTREE_H

#include <iostream>

#define ZERO 0
#define UNIT 1

namespace s21 {

template <typename Key, typename Value>
class MAVLTree {
 protected:
  struct Node;

 public:
  class Iterator;
  class ConstIterator;

  using key_type = Key;
  using value_type = Value;
  using reference = value_type &;
  using const_reference = const value_type &;
  using iterator = Iterator;
  using const_iterator = ConstIterator;
  using size_type = size_t;

  class Iterator {
   public:
    Iterator() : node_(nullptr), past_node_(nullptr){};

    Iterator(Node *node, Node *past_node = nullptr)
        : node_(node), past_node_(past_node){};

    Node *moveBack(Node *node) {
      if (node->left != nullptr) {
        return getMax(node->left);
      }
      Node *parent = node->parent;
      while (parent != nullptr && node == parent->left) {
        node = parent;
        parent = node->parent;
      }
      return parent;
    }

    iterator &operator++() {
      if (node_ != nullptr) {
        if (node_->right != nullptr) {
          node_ = node_->right;
          while (node_->left != nullptr) {
            node_ = node_->left;
          }
        } else {
          Node *parent = node_->parent;
          while (parent != nullptr && node_ == parent->right) {
            node_ = parent;
            parent = parent->parent;
          }
          node_ = parent;
        }
        return *this;
      }
      return *this;
    }

    iterator &operator++(int) {
      static iterator temp = *this;
      operator++();
      return temp;
    }

    iterator &operator--() {
      if (node_ == nullptr && past_node_ != nullptr) {
        *this = past_node_;
        return *this;
      }
      node_ = moveBack(node_);
      return *this;
    }

    iterator &operator--(int) {
      static iterator temp = *this;
      operator--();
      return temp;
    }

    reference operator*() {
      if (node_ == nullptr) {
        static Value fake = Value{};
        return fake;
      }
      return node_->value;
    }

    bool operator==(const Iterator &other) { return node_ == other.node_; }

    bool operator!=(const Iterator &other) { return node_ != other.node_; }

   protected:
    Node *node_;
    Node *past_node_;
  };

  class ConstIterator : public Iterator {
   public:
    ConstIterator() : Iterator(){};
    const_reference operator*() const { return Iterator::operator*(); }
  };

  MAVLTree() : root_(nullptr) {}

  MAVLTree(const MAVLTree &other) { root_ = copyTree(other.root_); }

  MAVLTree(MAVLTree &&other) {
    root_ = other.root_;
    other.root_ = nullptr;
  }

  ~MAVLTree() {
    if (root_ != nullptr) recursiveClear(root_);
    root_ = nullptr;
  }

  void insert(const Key &key, const Value &value) {
    root_ = recursiveInsert(root_, key, value);
  }

 protected:
  struct Node {
    Key key;
    Value value;
    int height;
    size_t count;
    Node *left;
    Node *right;
    Node *parent;

    Node(Key &key, Value &value)
        : key(key),
          value(value),
          height(UNIT),
          count(UNIT),
          left(nullptr),
          right(nullptr),
          parent(nullptr) {}
  };

  Node *root_;

  MAVLTree &operator=(MAVLTree &&other) {
    if (this != &other) {
      root_ = other.root_;
      other.root_ = nullptr;
    }
    return *this;
  }

  MAVLTree &operator=(const MAVLTree &other) {
    if (this != &other) {
      MAVLTree temp(other);
      recursiveClear(root_);
      *this = std::move(temp);
    }
    return *this;
  }

  int getHeight(Node *node) { return node == nullptr ? ZERO : node->height; }

  void updateHeight(Node *node) {
    if (node) {
      node->height =
          std::max(getHeight(node->left), getHeight(node->right)) + 1;
      updateHeight(node->left);
      updateHeight(node->right);
    }
  }

  int getBalance(Node *node) {
    return node == nullptr ? ZERO
                           : getHeight(node->left) - getHeight(node->right);
  }

  Node *rightRotation(Node *node) {
    Node *temp = node->left;
    node->left = temp->right;
    if (temp->right) {
      temp->right->parent = node;
    }
    temp->right = node;
    temp->parent = node->parent;
    node->parent = temp;
    updateHeight(node);
    updateHeight(temp);
    return temp;
  }

  Node *leftRotation(Node *node) {
    Node *temp = node->right;
    node->right = temp->left;
    if (temp->left) {
      temp->left->parent = node;
    }
    temp->left = node;
    temp->parent = node->parent;
    node->parent = temp;
    updateHeight(node);
    updateHeight(temp);
    return temp;
  }

  Node *balance(Node *node) {
    int getBal = getBalance(node);
    if (getBal > 1) {
      if (getBalance(node->right) != -1) {
        node = rightRotation(node);
      } else {
        node = leftRotation(node);
      }
    } else if (getBal < -1) {
      if (getBalance(node->left) != 1) {
        node = leftRotation(node);
      } else {
        node = rightRotation(node);
      }
    }
    return node;
  }

  static Node *getMax(Node *node) {
    if (node->right == nullptr) return node;
    return getMax(node->right);
  }

  static Node *getMin(Node *node) {
    if (node == nullptr) return nullptr;
    if (node->left == nullptr) return node;
    return getMin(node->left);
  }

  Node *recursiveInsert(Node *node, Key key, Value value) {
    if (node == nullptr) {
      Node *temp = new Node(key, value);
      return temp;
    }
    if (key < node->key) {
      node->left = recursiveInsert(node->left, key, value);
      node->left->parent = node;
    } else if (key > node->key) {
      node->right = recursiveInsert(node->right, key, value);
      node->right->parent = node;
    } else if (key == node->key) {
      node->count++;
    }
    updateHeight(node);
    return balance(node);
  }

  Node *recursiveClearNode(Node *node, Key key) {
    if (node == nullptr)
      return nullptr;
    else if (key < node->key)
      node->left = recursiveClearNode(node->left, key);
    else if (key > node->key)
      node->right = recursiveClearNode(node->right, key);
    else {
      if (node->left == nullptr || node->right == nullptr) {
        Node *node_parent = node->parent;
        Node *dupl_node = node;
        node = (node->left == nullptr) ? node->right : node->left;
        if (node != nullptr) node->parent = node_parent;
        delete dupl_node;
      } else {
        Node *maxInLeft = getMax(node->left);
        node->key = maxInLeft->key;
        node->value = maxInLeft->value;
        node->count = maxInLeft->count;
        node->left = recursiveClearNode(node->left, node->key);
      }
    }
    if (node != nullptr) {
      updateHeight(node);
      node = balance(node);
    }
    return node;
  }

  Node *recursiveFind(Node *node, Key key) {
    if (node == nullptr) return nullptr;
    if (node->key == key) return node;
    return (key < node->key) ? recursiveFind(node->left, key)
                             : recursiveFind(node->right, key);
  }

  Node *findRight(Node *node, const Key fkey) {
    Node *fNode = nullptr;

    if (node->right != nullptr) {
      if (fkey >= node->key && fkey >= getMin(node->right)->key)
        fNode = findRight(node->right, fkey);
      else if (fkey >= node->key && fkey < getMin(node->right)->key)
        return getMin(node->right);
    }

    if (node->left != nullptr)
      if (fkey < node->key && fkey >= getMax(node->left)->key) return node;

    if (fkey < node->key && fkey < getMin(node)->key) return getMin(node);

    if (node->left != nullptr)
      if (fkey < node->key) fNode = findRight(node->left, fkey);

    if (node->right == nullptr && node->left == nullptr) fNode = node;

    return fNode;
  }

  Node *findLeft(Node *node, const Key fkey) {
    Node *fNode = nullptr;

    if (node->left != nullptr) {
      if (fkey < node->key && fkey < getMax(node->left)->key)
        fNode = findLeft(node->left, fkey);
      else if (fkey < node->key && fkey >= getMax(node->left)->key)
        return node;
    }

    if (node->right != nullptr)
      if (fkey >= node->key && fkey < getMin(node->right)->key)
        return getMin(node->right);

    if (fkey > node->key && fkey >= getMax(node)->key) return root_;

    if (node->right != nullptr)
      if (fkey > node->key) fNode = findLeft(node->right, fkey);

    if (node->right == nullptr && node->left == nullptr) fNode = node;

    return fNode;
  }

  Node *findRange(Node *node, const Key fkey) {
    if (fkey < getMin(node)->key) return getMin(node);
    if (fkey > getMax(node)->key) return getMax(node);

    if (node == nullptr && node == root_) return nullptr;

    Node *fNode = nullptr;
    if (fkey < node->key && node == root_) fNode = findLeft(node->left, fkey);
    if (fkey >= node->key && node == root_)
      fNode = findRight(node->right, fkey);

    return fNode;
  }

  void recursiveClear(Node *node) {
    if (node == nullptr) return;
    if (node->left != nullptr) recursiveClear(node->left);
    if (node->right != nullptr) recursiveClear(node->right);
    delete node;
  }

  size_type recursiveSize(Node *node) {
    if (node == nullptr) return ZERO;
    size_type Count = ZERO;
    Count += node->count;
    Count += recursiveSize(node->left);
    Count += recursiveSize(node->right);
    return Count;
  }

  Node *copyTree(Node *node) {
    if (node == nullptr) return nullptr;
    Node *new_node = new Node(node->key, node->value);
    new_node->left = copyTree(node->left);
    new_node->right = copyTree(node->right);
    new_node->parent = node->parent;
    return new_node;
  }
};

}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_2_SRC_MULTISET_S21_MAVLTREE_H
