#ifndef CPP2_S21_CONTAINERS_2_SRC_SET_S21_SET_H
#define CPP2_S21_CONTAINERS_2_SRC_SET_S21_SET_H

#include <initializer_list>
#include <iostream>
#include <limits>
#include <utility>

#include "../avl_tree/s21_avltree.h"
#include "../vector/s21_vector.h"

namespace s21 {

template <typename T>
class set : public AVLTree<T, T> {
 public:
  using key_type = T;
  using value_type = T;
  using reference = value_type &;
  using iterator = typename AVLTree<T, T>::Iterator;
  using const_iterator = typename AVLTree<T, T>::ConstIterator;
  using size_type = size_t;

  set();
  set(std::initializer_list<value_type> const &items);
  set(const set &s);
  set(set &&s);
  ~set() = default;

  set<T> &operator=(const set &s);
  set<T> &operator=(set &&s);

  iterator begin();
  iterator end();

  bool empty();
  size_type size();
  size_type max_size();

  void clear();
  std::pair<iterator, bool> insert(const value_type &value);
  void erase(iterator pos);
  void swap(set &other);
  void merge(set &other);

  iterator find(const T &key);
  bool contains(const T &key);

  template <class... Args>
  s21::vector<std::pair<iterator, bool>> insert_many(Args &&...args);
};

template <typename T>
set<T>::set() : AVLTree<T, T>() {}

template <typename T>
set<T>::set(const std::initializer_list<value_type> &items) {
  for (auto &it : items) {
    AVLTree<T, T>::insert(it, it);
  }
}

template <typename T>
set<T>::set(const set &s) : AVLTree<T, T>(s) {}

template <typename T>
set<T>::set(set &&s) : AVLTree<T, T>(std::move(s)) {}

template <typename T>
set<T> &set<T>::operator=(const set<T> &s) {
  if (this != &s) {
    AVLTree<T, T>::operator=(s);
  }
  return *this;
}

template <typename T>
set<T> &set<T>::operator=(set<T> &&s) {
  if (this != &s) {
    AVLTree<T, T>::operator=(s);
  }
  return *this;
}

template <typename T>
typename set<T>::iterator set<T>::begin() {
  return iterator(AVLTree<T, T>::getMin(AVLTree<T, T>::root_));
}

template <typename T>
typename set<T>::iterator set<T>::end() {
  if (AVLTree<T, T>::root_ == nullptr) return begin();
  typename AVLTree<T, T>::Node *last_node =
      AVLTree<T, T>::getMax(AVLTree<T, T>::root_);
  iterator fake(nullptr, last_node);
  return fake;
}

template <typename T>
bool set<T>::empty() {
  return begin() == nullptr;
}

template <typename T>
size_t set<T>::size() {
  return AVLTree<T, T>::recursiveSize(AVLTree<T, T>::root_);
}

template <typename T>
size_t set<T>::max_size() {
  return std::numeric_limits<size_type>::max() /
         sizeof(typename AVLTree<T, T>::Node);
}

template <typename T>
void set<T>::clear() {
  if (AVLTree<T, T>::root_ != nullptr)
    AVLTree<T, T>::recursiveClear(AVLTree<T, T>::root_);
  AVLTree<T, T>::root_ = nullptr;
}

template <typename T>
std::pair<typename set<T>::iterator, bool> set<T>::insert(const T &value) {
  AVLTree<T, T>::insert(value, value);
  std::pair<typename AVLTree<T, T>::Iterator, bool> return_value;
  return_value =
      std::pair<iterator, bool>(find(value), AVLTree<T, T>::inserted);
  return return_value;
}

template <typename T>
void set<T>::erase(iterator pos) {
  AVLTree<T, T>::root_ =
      AVLTree<T, T>::recursiveClearNode(AVLTree<T, T>::root_, *pos);
}

template <typename T>
void set<T>::swap(set<T> &other) {
  std::swap(AVLTree<T, T>::root_, other.root_);
}

template <typename T>
void set<T>::merge(set<T> &other) {
  for (auto it = other.begin(); it != other.end(); it++) {
    insert(*it);
  }
  other.clear();
}

template <typename T>
typename set<T>::iterator set<T>::find(const T &key) {
  typename AVLTree<T, T>::Node *temp =
      AVLTree<T, T>::recursiveFind(AVLTree<T, T>::root_, key);
  return iterator(temp);
}

template <typename T>
bool set<T>::contains(const T &key) {
  typename AVLTree<T, T>::Node *temp =
      AVLTree<T, T>::recursiveFind(AVLTree<T, T>::root_, key);
  return temp != nullptr;
}

template <typename T>
template <class... Args>
s21::vector<std::pair<typename set<T>::iterator, bool>> set<T>::insert_many(
    Args &&...args) {
  s21::vector<std::pair<typename set<T>::iterator, bool>> vec;
  for (const auto &arg : {args...}) {
    vec.push_back(AVLTree<T, T>::insert(arg));
  }
  return vec;
}

}  // namespace s21
#endif  // CPP2_S21_CONTAINERS_2_SRC_SET_S21_SET_H