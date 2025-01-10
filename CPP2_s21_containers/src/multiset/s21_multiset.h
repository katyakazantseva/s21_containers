#ifndef CPP2_S21_CONTAINERS_2_SRC_MULTISET_S21_MULTISET_H
#define CPP2_S21_CONTAINERS_2_SRC_MULTISET_S21_MULTISET_H

#include <initializer_list>
#include <limits>

#include "../vector/s21_vector.h"
#include "s21_mavltree.h"

namespace s21 {

template <typename Key>
class multiset : public MAVLTree<Key, Key> {
 public:
  class MultisetIterator;
  class ConstMultisetIterator;

  using key_type = Key;
  using value_type = Key;
  using reference = value_type &;
  using const_reference = const value_type &;
  using iterator = MultisetIterator;
  using const_iterator = ConstMultisetIterator;
  using size_type = size_t;

  class MultisetIterator : public MAVLTree<Key, Key> {
   public:
    typename MAVLTree<Key, Key>::Node *node_;

    MultisetIterator() : node_(nullptr){};
    MultisetIterator(typename MAVLTree<Key, Key>::Node *node) : node_(node){};
    ~MultisetIterator() = default;

    typename MAVLTree<Key, Key>::Node *moveBack(
        typename MAVLTree<Key, Key>::Node *node) {
      if (node->left != nullptr) {
        return MAVLTree<Key, Key>::getMax(node->left);
      }
      typename MAVLTree<Key, Key>::Node *parent = node->parent;
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
          typename MAVLTree<Key, Key>::Node *parent = node_->parent;
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
        static Key fake = Key{};
        return fake;
      }

      return node_->value;
    }

    bool operator==(const MultisetIterator &other) {
      return node_ == other.node_;
    }

    bool operator!=(const MultisetIterator &other) {
      return node_ != other.node_;
    }
  };

  class ConstMultisetIterator : public MultisetIterator {
   public:
    ConstMultisetIterator() : MultisetIterator(){};
    const_reference operator*() const { return MultisetIterator::operator*(); }
  };

  multiset();
  multiset(std::initializer_list<value_type> const &items);
  multiset(const multiset &ms);
  multiset(multiset &&ms);

  ~multiset() = default;

  multiset<Key> &operator=(const multiset &ms);
  multiset<Key> &operator=(multiset &&ms);

  iterator begin();
  iterator end();

  bool empty();
  size_type size();
  size_type max_size();

  void clear();
  iterator insert(const value_type &value);
  void erase(iterator pos);
  void swap(multiset &other);
  void merge(multiset &other);

  size_type count(const Key &key);
  iterator find(const Key &key);
  bool contains(const Key &key);
  std::pair<iterator, iterator> equal_range(const Key &key);
  iterator lower_bound(const Key &key);
  iterator upper_bound(const Key &key);

  template <typename... Args>
  s21::vector<typename multiset<Key>::iterator> insert_many(Args &&...args);
};

template <typename Key>
multiset<Key>::multiset() : MAVLTree<Key, Key>() {}

template <typename Key>
multiset<Key>::multiset(std::initializer_list<value_type> const &items) {
  for (auto &it : items) {
    MAVLTree<Key, Key>::insert(it, it);
  }
}

template <typename Key>
multiset<Key>::multiset(const multiset &ms) : MAVLTree<Key, Key>(ms) {}

template <typename Key>
multiset<Key>::multiset(multiset &&ms) : MAVLTree<Key, Key>(std::move(ms)) {}

template <typename Key>
multiset<Key> &multiset<Key>::operator=(const multiset &ms) {
  if (this != &ms) {
    MAVLTree<Key, Key>::operator=(ms);
  }

  return *this;
}

template <typename Key>
multiset<Key> &multiset<Key>::operator=(multiset &&ms) {
  if (this != &ms) {
    MAVLTree<Key, Key>::operator=(ms);
  }

  return *this;
}

template <typename Key>
typename multiset<Key>::iterator multiset<Key>::begin() {
  return iterator(MAVLTree<Key, Key>::getMin(MAVLTree<Key, Key>::root_));
}

template <typename Key>
typename multiset<Key>::iterator multiset<Key>::end() {
  if (MAVLTree<Key, Key>::root_ == nullptr)
    return begin();
  else
    return iterator(MAVLTree<Key, Key>::getMax(MAVLTree<Key, Key>::root_));
}

template <typename Key>
bool multiset<Key>::empty() {
  return (this->begin() == this->end());
}

template <typename Key>
size_t multiset<Key>::size() {
  return MAVLTree<Key, Key>::recursiveSize(MAVLTree<Key, Key>::root_);
}

template <typename Key>
size_t multiset<Key>::max_size() {
  return std::numeric_limits<size_type>::max() /
         sizeof(typename MAVLTree<Key, Key>::Node);
}

template <typename Key>
void multiset<Key>::clear() {
  if (MAVLTree<Key, Key>::root_ != nullptr)
    MAVLTree<Key, Key>::recursiveClear(MAVLTree<Key, Key>::root_);

  MAVLTree<Key, Key>::root_ = nullptr;
}

template <typename Key>
typename multiset<Key>::iterator multiset<Key>::insert(
    const value_type &value) {
  MAVLTree<Key, Key>::insert(value, value);
  iterator return_value = find(value);
  return return_value;
}

template <typename Key>
void multiset<Key>::erase(iterator pos) {
  MAVLTree<Key, Key>::root_ =
      MAVLTree<Key, Key>::recursiveClearNode(MAVLTree<Key, Key>::root_, *pos);
}

template <typename Key>
void multiset<Key>::swap(multiset<Key> &other) {
  std::swap(MAVLTree<Key, Key>::root_, other.root_);
}

template <typename Key>
void multiset<Key>::merge(multiset<Key> &other) {
  for (auto it = other.begin(); it != other.end(); it++) {
    MAVLTree<Key, Key>::insert(*it, *it);
  }
  other.clear();
}

template <typename Key>
typename multiset<Key>::size_type multiset<Key>::count(const Key &key) {
  typename MAVLTree<Key, Key>::Node *node =
      MAVLTree<Key, Key>::recursiveFind(MAVLTree<Key, Key>::root_, key);
  size_type x = ZERO;

  return (node != nullptr) ? node->count : x;
}

template <typename Key>
typename multiset<Key>::iterator multiset<Key>::find(const Key &key) {
  typename MAVLTree<Key, Key>::Node *node =
      MAVLTree<Key, Key>::recursiveFind(MAVLTree<Key, Key>::root_, key);

  iterator find(node);
  return find;
}

template <typename Key>
bool multiset<Key>::contains(const Key &key) {
  iterator it = find(key);
  return (it != nullptr) ? true : false;
}

template <typename Key>
std::pair<typename multiset<Key>::iterator, typename multiset<Key>::iterator>
multiset<Key>::equal_range(const Key &key) {
  std::pair<typename multiset<Key>::iterator, typename multiset<Key>::iterator>
      result;

  typename MAVLTree<Key, Key>::Node *node =
      MAVLTree<Key, Key>::recursiveFind(MAVLTree<Key, Key>::root_, key);

  if (node == nullptr) {
    node = MAVLTree<Key, Key>::findRange(MAVLTree<Key, Key>::root_, key);
    result.first.node_ = result.second.node_ = node;
  } else {
    result.first.node_ = node;
    result.second.node_ =
        MAVLTree<Key, Key>::findRange(MAVLTree<Key, Key>::root_, node->key);
  }

  return result;
}

template <typename Key>
typename multiset<Key>::iterator multiset<Key>::lower_bound(const Key &key) {
  if (key > MAVLTree<Key, Key>::getMax(MAVLTree<Key, Key>::root_)->key)
    throw std::out_of_range("lower_bound: Too big key\n");

  typename MAVLTree<Key, Key>::Node *node =
      MAVLTree<Key, Key>::recursiveFind(MAVLTree<Key, Key>::root_, key);

  iterator result;

  if (node != nullptr)
    result.node_ = node;
  else
    result.node_ =
        MAVLTree<Key, Key>::findRange(MAVLTree<Key, Key>::root_, key);

  return result;
}

template <typename Key>
typename multiset<Key>::iterator multiset<Key>::upper_bound(const Key &key) {
  if (key > MAVLTree<Key, Key>::getMax(MAVLTree<Key, Key>::root_)->key)
    throw std::out_of_range("upper_bound: Too big key\n");

  typename MAVLTree<Key, Key>::Node *node =
      MAVLTree<Key, Key>::findRange(MAVLTree<Key, Key>::root_, key);

  iterator result;

  result.node_ = node;

  return result;
}

template <typename Key>
template <typename... Args>
s21::vector<typename multiset<Key>::iterator> multiset<Key>::insert_many(
    Args &&...args) {
  s21::vector<typename multiset<Key>::iterator> vec;
  for (const auto &arg : {args...}) {
    vec.push_back(insert(arg));
  }

  return vec;
}
}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_2_SRC_MULTISET_S21_MULTISET_H