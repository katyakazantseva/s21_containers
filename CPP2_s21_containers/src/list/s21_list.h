#ifndef CPP_2_S21_CONTAINERS_2_SRC_LIST_S21_LIST_H
#define CPP_2_S21_CONTAINERS_2_SRC_LIST_S21_LIST_H

#include <cstdlib>
#include <functional>
#include <initializer_list>
#include <iostream>
#include <limits>
#include <ostream>
#include <utility>

#include "Iterator.h"

namespace s21 {

template <class T>
class list {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = Iterator<list<value_type>>;
  using const_iterator = const Iterator<list<value_type>>;
  using size_type = size_t;

  list();

  explicit list(size_type n);

  list(std::initializer_list<value_type> const &items);

  list(const list &other)
      : size_(0u), head_(nullptr), tail_(nullptr), fake_(nullptr) {
    for (const auto &i : other) {
      push_back(i);
    }
  };

  list(list &&other) noexcept;

  ~list() { clear(); };

  bool operator==(const list &other) const;
  bool operator!=(const list &other) const;

  list &operator=(const list &other) noexcept;

  list &operator=(list &&other) noexcept;

  list &operator=(std::initializer_list<value_type> const &items);

  const_reference front() const {
    if (head_ == nullptr) {
      throw std::out_of_range("list is empty.");
    }
    return *iterator(head_);
  };

  const_reference back() const {
    if (tail_ == nullptr) {
      throw std::out_of_range("list is empty.");
    }
    return *iterator(tail_);
  };

  iterator begin() { return iterator(head_); };
  const_iterator begin() const { return iterator(head_); };

  const_iterator cbegin() const;

  iterator end() { return iterator(fake_); };

  const_iterator end() const { return iterator(fake_); };

  const_iterator cend() const;

  bool empty() { return size() == 0; };

  size_type size() const { return size_; };

  size_type max_size() {
    return std::numeric_limits<size_type>::max() / 2 / sizeof(Node<value_type>);
  }

  void clear();

  iterator insert(iterator pos, const_reference value);

  iterator erase(iterator pos);

  void push_back(const_reference value);

  void pop_back();

  void push_front(const_reference value);

  void pop_front();

  void swap(list &other);

  void merge(list &other);

  void splice(const_iterator pos, list &other);

  void reverse();

  void unique();

  void sort();

  template <class... Args>
  iterator insert_many(const_iterator pos, Args &&...args) {
    auto pos_current = pos;
    for (auto &arg : {args...}) {
      insert(pos_current, arg);
    }
    return pos;
  }

  template <class... Args>
  void insert_many_back(Args &&...args) {
    for (auto &arg : {args...}) {
      push_back(arg);
    }
  }

  template <class... Args>
  void insert_many_front(Args &&...args) {
    for (auto &arg : {args...}) {
      push_front(arg);
    }
  }

  T &operator[](const int index);

 private:
  size_type size_;

  Node<value_type> *head_;
  Node<value_type> *tail_;
  Node<value_type> *fake_;
};

template <typename T>
list<T>::list() : size_(0U), head_(nullptr), tail_(nullptr), fake_(nullptr) {
  auto *fake_node = new Node<value_type>();
  fake_ = head_ = tail_ = fake_node;
  fake_node->pNext = head_;
  fake_node->pPrev = tail_;
}

template <typename T>
list<T>::list(size_type n)
    : size_(0U), head_(nullptr), tail_(nullptr), fake_(nullptr) {
  for (size_t i = 0; i < n; i++) {
    push_back(const_reference{});
  }
}

template <typename T>
list<T>::list(std::initializer_list<value_type> const &items)
    : size_(0U), head_(nullptr), tail_(nullptr), fake_(nullptr) {
  for (const auto &i : items) {
    push_back(i);
  }
}

template <typename T>
list<T>::list(list<T> &&other) noexcept {
  if (this != &other && !other.empty()) {
    head_ = other.head_;
    tail_ = other.tail_;
    fake_ = other.fake_;
    size_ = other.size_;

    other.head_ = other.tail_ = other.fake_ = nullptr;
    other.size_ = 0;
  }
}

template <typename T>
list<T> &list<T>::operator=(const list &other) noexcept {
  if (this != &other) {
    clear();
    for (const auto &i : other) {
      push_back(i);
    }
  }
  return *this;
}

template <typename T>
list<T> &list<T>::operator=(list<T> &&other) noexcept {
  if (this != &other) {
    clear();
    head_ = other.head_;
    tail_ = other.tail_;
    fake_ = other.fake_;
    size_ = other.size_;

    other.head_ = other.tail_ = other.fake_ = nullptr;
    other.size_ = 0;
  }
  return *this;
}

template <typename T>
list<T> &list<T>::operator=(std::initializer_list<value_type> const &items) {
  clear();
  for (const auto &i : items) {
    push_back(i);
  }
  return *this;
}

template <typename T>
void list<T>::push_back(const_reference value) {
  auto *new_node = new Node<value_type>;
  Node<value_type> *fake_node;
  if (size_ == 0) {
    fake_node = (fake_ == nullptr ? new Node<value_type>() : fake_);
    new_node->pNext = new_node->pPrev = fake_node;
    fake_node->pNext = fake_node->pPrev = new_node;
    head_ = tail_ = new_node;
    fake_ = fake_node;
  } else {
    new_node->pPrev = tail_;
    tail_->pNext = new_node;
    new_node->pNext = fake_;
    fake_->pPrev = new_node;
    tail_ = new_node;
  }
  size_++;
  new_node->data = value;
  fake_->data = size_;
}

template <typename T>
void list<T>::push_front(const_reference value) {
  auto *new_node = new Node<value_type>;
  Node<value_type> *fake_node;
  if (size_ == 0) {
    fake_node = (fake_ == nullptr ? new Node<value_type>() : fake_);
    new_node->pNext = new_node->pPrev = fake_node;
    fake_node->pNext = fake_node->pPrev = new_node;
    head_ = tail_ = new_node;
    fake_ = fake_node;
  } else {
    new_node->pNext = head_;
    head_->pPrev = new_node;
    new_node->pPrev = fake_;
    fake_->pNext = new_node;
    head_ = new_node;
  }
  new_node->data = value;
  ++size_;
  fake_->data = size_;
}

template <typename T>
T &list<T>::operator[](const int index) {
  int counter = 0;
  Node<value_type> *current = this->head_;
  while (current->pNext != fake_) {
    if (counter == index) {
      return current->data;
    }
    current = current->pNext;
    counter++;
  }
  return current->data;
}

template <typename T>
void list<T>::pop_back() {
  if (size_ > 0) {
    Node<value_type> *tmp = tail_;
    tail_ = fake_->pPrev = tail_->pPrev;
    delete tmp;
    size_--;
    if (!size_ && fake_ != nullptr) {
      delete fake_;
      fake_ = head_ = tail_ = nullptr;
    } else {
      tail_->pNext = fake_;
    }
  }
}

template <typename T>
void list<T>::pop_front() {
  if (size_ > 0) {
    Node<value_type> *tmp = head_;
    head_ = fake_->pNext = head_->pNext;
    delete tmp;
    size_--;
    if (!size_) {
      delete fake_;
      fake_ = head_ = tail_ = nullptr;
    } else {
      head_->pPrev = fake_;
    }
  }
}

template <typename T>
void list<T>::clear() {
  while (size_ != 0 && fake_ != nullptr && head_ != nullptr) {
    pop_back();
  }
  if (fake_ != nullptr) {
    delete fake_;
    fake_ = head_ = tail_ = nullptr;
  }
}

template <typename T>
typename list<T>::iterator list<T>::insert(iterator pos,
                                           const_reference value) {
  Node<value_type> *insert_node;
  if (pos == begin()) {
    push_front(value);
    insert_node = head_;
  } else if (pos == end()) {
    push_back(value);
    insert_node = tail_;
  } else {
    insert_node = new Node<value_type>(value);
    Node<value_type> *current_pos = pos.get_node();

    insert_node->pNext = current_pos;
    insert_node->pPrev = current_pos->pPrev;

    current_pos->pPrev->pNext = insert_node;
    current_pos->pPrev = insert_node;
    size_++;
  }
  return iterator(insert_node);
}

template <typename T>
typename list<T>::iterator list<T>::erase(iterator pos) {
  if (size_) {
    Node<value_type> *last_pos = fake_;
    if (pos == begin()) {
      pop_front();
      last_pos = head_;
    } else if (pos == --end()) {
      pop_back();
      last_pos = fake_;
    } else if (pos != end()) {
      Node<value_type> *current_pos = pos.get_node();
      current_pos->pPrev->pNext = current_pos->pNext;
      current_pos->pNext->pPrev = current_pos->pPrev;
      last_pos = current_pos->pNext;
      delete current_pos;
      size_--;
    }
    fake_->data = size_;
    return iterator(last_pos);
  }
  return end();
}

template <typename T>
void list<T>::swap(list<T> &other) {
  if (this != &other) {
    Node<value_type> *tmp_head_ = head_;
    Node<value_type> *tmp_tail_ = tail_;
    Node<value_type> *tmp_fake_ = fake_;
    size_type tmp_size_ = size_;

    head_ = other.head_;
    tail_ = other.tail_;
    fake_ = other.fake_;
    size_ = other.size_;

    other.head_ = tmp_head_;
    other.tail_ = tmp_tail_;
    other.fake_ = tmp_fake_;
    other.size_ = tmp_size_;
  }
}

template <typename T>
void list<T>::merge(list<T> &other) {
  if (this == &other) return;

  s21::list<value_type> result;
  int i = 0;
  int j = 0;
  int i_size = size();
  int j_size = other.size();
  while (i != i_size && j != j_size) {
    if (other.operator[](j) > operator[](i)) {
      result.push_back(operator[](i));
      i++;
    } else {
      result.push_back(other.operator[](j));
      j++;
    }
  }
  while (i != i_size) {
    result.push_back(operator[](i));
    i++;
  }
  while (j != j_size) {
    result.push_back(other.operator[](j));
    j++;
  }
  *this = result;
  other.clear();
}

template <typename T>
void list<T>::splice(list::const_iterator pos, list &other) {
  if (this == &other || other.size() == 0) return;

  Node<value_type> *current_pos = pos.get_node();

  other.head_->pPrev = current_pos->pPrev;
  other.tail_->pNext = current_pos;

  current_pos->pPrev->pNext = other.head_;
  current_pos->pPrev = other.tail_;

  head_ = fake_->pNext;
  tail_ = fake_->pPrev;
  size_ += other.size_;

  delete other.fake_;
  other.head_ = other.tail_ = other.fake_ = nullptr;
  other.size_ = 0;
}

template <typename T>
void list<T>::reverse() {
  Node<value_type> *current_node = fake_->pNext;
  Node<value_type> *temp_node;
  Node<value_type> *prev_node = current_node->pPrev;
  while (current_node != fake_) {
    temp_node = current_node->pNext;
    current_node->pNext = prev_node;
    prev_node = current_node;
    current_node = temp_node;
  }
  head_ = prev_node;
  fake_->pNext = head_;
}

template <typename T>
void list<T>::unique() {
  iterator current(head_);
  iterator next;
  while (current != end()) {
    next = current;
    ++next;
    while (next != end()) {
      if (*current == *next) {
        next = erase(next);
      } else {
        ++next;
      }
    }
    ++current;
  }
}

template <typename T>
void list<T>::sort() {
  if (size_ <= 1) return;

  size_type middle_idx = size_ / 2;
  size_type second_size = size_ - middle_idx;
  Node<value_type> *second_head = head_;
  Node<value_type> *second_end = fake_->pPrev;

  for (size_type i = 0; i < middle_idx; ++i) {
    second_head = second_head->pNext;
  }

  tail_ = second_head->pPrev;
  tail_->pNext = fake_;
  fake_->pPrev = tail_;
  size_ = middle_idx;

  list<T> right_half;
  right_half.head_ = second_head;
  right_half.tail_ = second_end;

  right_half.fake_->pNext = right_half.head_;
  right_half.fake_->pPrev = right_half.tail_;

  right_half.tail_->pNext = right_half.fake_;
  right_half.head_->pPrev = right_half.fake_;
  right_half.size_ = second_size;

  this->sort();
  right_half.sort();

  merge(right_half);
}

template <typename T>
typename list<T>::const_iterator list<T>::cbegin() const {
  return const_iterator(head_);
}

template <typename T>
typename list<T>::const_iterator list<T>::cend() const {
  return const_iterator(fake_);
}

template <typename T>
bool list<T>::operator==(const list<T> &other) const {
  bool is_equal = false;
  is_equal = (size() == other.size());

  iterator it_1 = begin();
  iterator it_2 = other.begin();

  while (is_equal && it_1 != cend() && it_2 != other.end()) {
    is_equal = *it_1++ == *it_2++;
  }
  return is_equal;
}

template <class T>
bool list<T>::operator!=(const list<T> &other) const {
  return !(*this == other);
}

}  // namespace s21

#endif  // CPP_2_S21_CONTAINERS_2_SRC_LIST_S21_LIST_H
