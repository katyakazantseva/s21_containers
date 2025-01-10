#ifndef CPP2_S21_CONTAINERS_2_SRC_MAP_S21_MAP_H
#define CPP2_S21_CONTAINERS_2_SRC_MAP_S21_MAP_H

#include <initializer_list>
#include <iostream>
#include <limits>
#include <utility>

#include "../avl_tree/s21_avltree.h"
#include "../vector/s21_vector.h"

namespace s21 {
template <typename Key, typename T>
class map : public AVLTree<Key, T> {
 public:
  class MapIterator;
  class ConstMapIterator;

  using key_type = Key;
  using mapped_type = T;
  using value_type = std::pair<const key_type, mapped_type>;
  using reference = value_type &;
  using const_reference = const value_type &;
  using iterator = MapIterator;
  using const_iterator = ConstMapIterator;
  using size_type = size_t;

  map();
  map(std::initializer_list<value_type> const &items);
  map(const map &m);
  map(map &&m);
  ~map() = default;

  map<Key, T> &operator=(const map &m);
  map<Key, T> &operator=(map &&m);

  mapped_type &at(const Key &key);
  mapped_type &operator[](const Key &key);

  iterator begin();
  iterator end();

  bool empty();
  size_type size();
  size_type max_size();

  void clear();
  std::pair<iterator, bool> insert(const value_type &value);
  std::pair<iterator, bool> insert(const Key &key, const T &obj);
  std::pair<iterator, bool> insert_or_assign(const Key &key, const T &obj);
  void erase(iterator pos);
  void swap(map &other);
  void merge(map &other);

  bool contains(const Key &key);

  template <class... Args>
  s21::vector<std::pair<iterator, bool>> insert_many(Args &&...args);

  class MapIterator : public AVLTree<Key, T>::Iterator {
   public:
    MapIterator() : AVLTree<Key, T>::Iterator(){};
    MapIterator(typename AVLTree<Key, T>::Node *node,
                typename AVLTree<Key, T>::Node *past_node = nullptr)
        : AVLTree<Key, T>::Iterator(node, past_node = nullptr){};
    value_type &operator*() {
      if (AVLTree<Key, T>::Iterator::node_ == nullptr) {
        static value_type fake = value_type{};
        return fake;
      }
      std::pair<const key_type, mapped_type> pr =
          std::make_pair(AVLTree<Key, T>::Iterator::node_->key,
                         AVLTree<Key, T>::Iterator::node_->value);
      std::pair<const key_type, mapped_type> &ref = pr;
      return ref;
    }
  };

  class ConstMapIterator : public MapIterator {
   public:
    ConstMapIterator() : MapIterator(){};
    ConstMapIterator(typename AVLTree<Key, T>::Node *node,
                     typename AVLTree<Key, T>::Node *past_node = nullptr)
        : MapIterator(node, past_node = nullptr){};
    const_reference operator*() const { return MapIterator::operator*(); };
  };
};

template <typename Key, typename T>
map<Key, T>::map() : AVLTree<Key, T>() {}

template <typename Key, typename T>
map<Key, T>::map(const std::initializer_list<value_type> &items) {
  for (auto &it : items) {
    AVLTree<Key, T>::insert(it.first, it.second);
  }
}

template <typename Key, typename T>
map<Key, T>::map(const map<Key, T> &m) : AVLTree<Key, T>(m) {}

template <typename Key, typename T>
map<Key, T>::map(map<Key, T> &&m) : AVLTree<Key, T>(std::move(m)) {}

template <typename Key, typename T>
map<Key, T> &map<Key, T>::operator=(const map<Key, T> &m) {
  if (this != &m) {
    AVLTree<Key, T>::operator=(m);
  }
  return *this;
}

template <typename Key, typename T>
map<Key, T> &map<Key, T>::operator=(map<Key, T> &&m) {
  if (this != &m) {
    AVLTree<Key, T>::operator=(m);
  }
  return *this;
}

template <typename Key, typename T>
typename map<Key, T>::mapped_type &map<Key, T>::at(const Key &key) {
  auto it = AVLTree<Key, T>::recursiveFind(AVLTree<Key, T>::root_, key);
  if (it == nullptr) {
    throw std::out_of_range("Out of range. Index exceeds container bounds");
  }
  return it->value;
}

template <typename Key, typename T>
typename map<Key, T>::mapped_type &map<Key, T>::operator[](const Key &key) {
  auto it = AVLTree<Key, T>::recursiveFind(AVLTree<Key, T>::root_, key);
  if (it == nullptr) {
    insert(std::make_pair(key, T()));
    it = AVLTree<Key, T>::recursiveFind(AVLTree<Key, T>::root_, key);
  }
  return it->value;
}

template <typename Key, typename T>
typename map<Key, T>::iterator map<Key, T>::begin() {
  return map<Key, T>::MapIterator(
      AVLTree<Key, T>::getMin(AVLTree<Key, T>::root_));
}

template <typename Key, typename T>
typename map<Key, T>::iterator map<Key, T>::end() {
  if (AVLTree<Key, T>::root_ == nullptr) return begin();
  typename AVLTree<Key, T>::Node *last_node =
      AVLTree<Key, T>::getMax(AVLTree<Key, T>::root_);
  MapIterator fake(nullptr, last_node);
  return fake;
}

template <typename Key, typename T>
bool map<Key, T>::empty() {
  return begin() == nullptr;
}

template <typename Key, typename T>
size_t map<Key, T>::size() {
  return AVLTree<T, T>::recursiveSize(AVLTree<T, T>::root_);
}

template <typename Key, typename T>
size_t map<Key, T>::max_size() {
  return std::numeric_limits<size_type>::max() /
         sizeof(typename AVLTree<T, T>::Node);
}

template <typename Key, typename T>
void map<Key, T>::clear() {
  if (AVLTree<T, T>::root_ != nullptr)
    AVLTree<T, T>::recursiveClear(AVLTree<T, T>::root_);
  AVLTree<T, T>::root_ = nullptr;
}

template <typename Key, typename T>
std::pair<typename map<Key, T>::iterator, bool> map<Key, T>::insert(
    const value_type &value) {
  AVLTree<Key, T>::insert(value.first, value.second);
  std::pair<MapIterator, bool> return_value;
  return_value = std::pair<iterator, bool>(
      AVLTree<Key, T>::recursiveFind(AVLTree<Key, T>::root_, value.first),
      AVLTree<Key, T>::inserted);
  return return_value;
}

template <typename Key, typename T>
std::pair<typename map<Key, T>::iterator, bool> map<Key, T>::insert(
    const Key &key, const T &obj) {
  AVLTree<Key, T>::insert(key, obj);
  std::pair<MapIterator, bool> return_value;
  return_value = std::pair<iterator, bool>(
      AVLTree<Key, T>::recursiveFind(AVLTree<Key, T>::root_, key),
      AVLTree<Key, T>::inserted);
  return return_value;
}

template <typename Key, typename T>
std::pair<typename map<Key, T>::iterator, bool> map<Key, T>::insert_or_assign(
    const Key &key, const T &obj) {
  auto it = AVLTree<Key, T>::recursiveFind(AVLTree<Key, T>::root_, key);
  std::pair<MapIterator, bool> return_value;
  if (it != nullptr) {
    AVLTree<Key, T>::recursiveClearNode(AVLTree<Key, T>::root_, key);
  }
  AVLTree<Key, T>::insert(key, obj);
  return_value = std::pair<iterator, bool>(
      AVLTree<Key, T>::recursiveFind(AVLTree<Key, T>::root_, key),
      AVLTree<Key, T>::inserted);
  return return_value;
}

template <typename Key, typename T>
void map<Key, T>::erase(map::iterator pos) {
  AVLTree<T, T>::root_ =
      AVLTree<T, T>::recursiveClearNode(AVLTree<T, T>::root_, (*pos).first);
}

template <typename Key, typename T>
void map<Key, T>::swap(map<Key, T> &other) {
  std::swap(AVLTree<T, T>::root_, other.root_);
}

template <typename Key, typename T>
void map<Key, T>::merge(map<Key, T> &other) {
  for (auto it : other) {
    AVLTree<T, T>::insert(it.first, it.second);
  }
  other.clear();
}

template <typename Key, typename T>
bool map<Key, T>::contains(const Key &key) {
  typename AVLTree<T, T>::Node *temp =
      AVLTree<T, T>::recursiveFind(AVLTree<T, T>::root_, key);
  return temp != nullptr;
}

template <typename Key, typename T>
template <class... Args>
s21::vector<std::pair<typename map<Key, T>::iterator, bool>>
map<Key, T>::insert_many(Args &&...args) {
  s21::vector<std::pair<typename map<Key, T>::iterator, bool>> vec;
  for (const auto &arg : {args...}) {
    vec.push_back(insert(arg));
  }
  return vec;
}

}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_2_SRC_MAP_S21_MAP_H