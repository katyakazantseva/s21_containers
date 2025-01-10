#ifndef CPP_2_S21_CONTAINERS_2_SRC_LIST_S21_ITERATOR_H
#define CPP_2_S21_CONTAINERS_2_SRC_LIST_S21_ITERATOR_H

#include "s21_list.h"

namespace s21 {

template <typename T>
struct Node {
  using value_type = T;
  using const_reference = const T &;

  Node() : data(), pNext(nullptr), pPrev(nullptr) {}

  explicit Node(const_reference value) {
    data = value;
    pNext = nullptr;
    pPrev = nullptr;
  }

  ~Node() = default;

  value_type data;
  Node<value_type> *pNext;
  Node<value_type> *pPrev;
};

template <typename Container>
class Iterator {
 public:
  using value_type = typename Container::value_type;
  using pointer_type = Node<value_type> *;
  using reference_type = value_type &;

  Iterator() noexcept : current_node_(nullptr), iterator_pos_(0) {}

  explicit Iterator(pointer_type node)
      : current_node_(node), iterator_pos_(0) {}

  Iterator(const Iterator &other) = default;

  Iterator &operator=(const Iterator &other) = default;

  reference_type operator*() const { return current_node_->data; }

  Iterator &operator++() {
    current_node_ = current_node_->pNext;
    iterator_pos_++;
    return *this;
  }

  Iterator operator++(int) {
    Iterator tmp = *this;
    current_node_ = current_node_->pNext;
    iterator_pos_++;
    return tmp;
  }

  Iterator &operator--() {
    current_node_ = current_node_->pPrev;
    iterator_pos_--;
    return *this;
  }

  Iterator &operator--(int) {
    static Iterator tmp = *this;
    current_node_ = current_node_->pPrev;
    iterator_pos_--;
    return tmp;
  }

  bool operator==(const Iterator &other) const {
    return (current_node_ == other.current_node_);
  }

  bool operator!=(const Iterator &other) const {
    return current_node_ != other.current_node_;
  }

  pointer_type get_node() const { return current_node_; }

  int get_iterator_pos_() const { return iterator_pos_; }

 private:
  pointer_type current_node_;
  int iterator_pos_;
};

template <typename Container>
class ConstIterator {
 public:
  using value_type = const typename Container::value_type;
  using pointer_type = Node<value_type> *;
  using reference_type = value_type &;

  ConstIterator() noexcept : current_node_(nullptr), iterator_pos_(0) {}

  explicit ConstIterator(pointer_type node)
      : current_node_(node), iterator_pos_(0) {}

  ConstIterator(const ConstIterator &other) = default;

  ConstIterator &operator=(const ConstIterator &other) = default;

  reference_type operator*() const { return current_node_->data; }

  ConstIterator &operator++() {
    current_node_ = current_node_->pNext;
    iterator_pos_++;
    return *this;
  }

  ConstIterator operator++(int) {
    ConstIterator tmp = *this;
    current_node_ = current_node_->pNext;
    iterator_pos_++;
    return tmp;
  }

  ConstIterator &operator--() {
    current_node_ = current_node_->pPrev;
    iterator_pos_--;
    return *this;
  }

  ConstIterator &operator--(int) {
    ConstIterator tmp = *this;
    current_node_ = current_node_->pPrev;
    iterator_pos_--;
    return tmp;
  }

  bool operator==(const ConstIterator &other) const {
    return (current_node_ == other.current_node_);
  }

  bool operator!=(const ConstIterator &other) const {
    return current_node_ != other.current_node_;
  }

  pointer_type get_node() const { return current_node_; }

  int get_iterator_pos() const { return iterator_pos_; }

 private:
  pointer_type current_node_;
  int iterator_pos_;
};
}  // namespace s21
#endif  // CPP_2_S21_CONTAINERS_2_SRC_LIST_S21_ITERATOR_H