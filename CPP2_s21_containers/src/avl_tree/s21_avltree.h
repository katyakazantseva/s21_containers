#ifndef CPP_2_S21_CONTAINERS_2_SRC_AVL_TREE_S21_AVLTREE_H
#define CPP_2_S21_CONTAINERS_2_SRC_AVL_TREE_S21_AVLTREE_H

#include <iostream>

namespace s21 {

template <typename Key, typename Value>
class AVLTree {
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

  AVLTree() : root_(nullptr), inserted(false) {}

  AVLTree(const AVLTree &other) { root_ = copyTree(other.root_); }

  AVLTree(AVLTree &&other) {
    root_ = other.root_;
    other.root_ = nullptr;
  }

  ~AVLTree() {
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
    Node *left;
    Node *right;
    Node *parent;

    Node(Key &key, Value &value)
        : key(key),
          value(value),
          height(1),
          left(nullptr),
          right(nullptr),
          parent(nullptr) {}
  };

  Node *root_;
  bool inserted;

  AVLTree &operator=(const AVLTree &other) {
    if (this != &other) {
      AVLTree temp(other);
      recursiveClear(root_);
      *this = std::move(temp);
    }
    return *this;
  }

  AVLTree &operator=(AVLTree &&other) {
    if (this != &other) {
      root_ = other.root_;
      other.root_ = nullptr;
    }
    return *this;
  }

  int getHeight(Node *node) { return node == nullptr ? 0 : node->height; }

  void updateHeight(Node *node) {
    if (node) {
      node->height =
          std::max(getHeight(node->left), getHeight(node->right)) + 1;
      updateHeight(node->left);
      updateHeight(node->right);
    }
  }

  int getBalance(Node *node) {
    return node == nullptr ? 0 : getHeight(node->left) - getHeight(node->right);
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
    this->inserted = false;
    if (node == nullptr) {
      Node *temp = new Node(key, value);
      this->inserted = true;
      return temp;
    }
    if (key < node->key) {
      node->left = recursiveInsert(node->left, key, value);
      node->left->parent = node;
    } else if (key > node->key) {
      node->right = recursiveInsert(node->right, key, value);
      node->right->parent = node;
    } else {
      this->inserted = false;
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
        node->left = recursiveClearNode(node->left, maxInLeft->key);
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

  void recursiveClear(Node *node) {
    if (node == nullptr) return;
    if (node->left != nullptr) recursiveClear(node->left);
    if (node->right != nullptr) recursiveClear(node->right);
    delete node;
  }

  size_type recursiveSize(Node *node) {
    if (node == nullptr) return 0;
    size_type left_size = recursiveSize(node->left);
    size_type right_size = recursiveSize(node->right);
    return 1 + left_size + right_size;
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

#endif  // CPP_2_S21_CONTAINERS_2_SRC_AVL_TREE_S21_AVLTREE_H