#ifndef CPP2_S21_CONTAINERS_2_SRC_ARRAY_S21_ARRAY_H
#define CPP2_S21_CONTAINERS_2_SRC_ARRAY_S21_ARRAY_H

#include <initializer_list>
#include <iostream>

#define ZERO 0
#define UNIT 1

namespace s21 {
template <typename T, size_t Size>
class array {
 public:
  using value_type = T;
  using reference = T&;
  using const_reference = const T&;
  using iterator = T*;
  using const_iterator = const T*;
  using size_type = size_t;

  array();
  array(std::initializer_list<value_type> const& items);
  array(const array& a);
  array(array&& a);
  ~array();

  array& operator=(const array& a);
  array& operator=(array&& a);
  reference operator[](size_type pos);

  reference at(size_type pos);
  const_reference front();
  const_reference back();
  bool empty();
  size_type size();
  size_type max_size();
  void swap(array& other);
  void fill(const_reference value);

  iterator data();
  iterator begin();
  iterator end();

 private:
  size_t size_;
  value_type* array_;
};

template <typename T, size_t Size>
array<T, Size>::array() : size_(Size), array_(new T[size_]()) {}

template <typename T, size_t Size>
array<T, Size>::array(std::initializer_list<value_type> const& item)
    : size_(Size) {
  if (item.size() > size_) throw std::invalid_argument("Too many initializers");
  array_ = new T[size_]();
  std::copy(item.begin(), item.end(), array_);
}

template <typename T, size_t Size>
array<T, Size>::array(const array& a) : size_(a.size_) {
  array_ = new T[size_];
  for (size_t i = ZERO; i < size_; i++) {
    array_[i] = a.array_[i];
  }
}

template <typename T, size_t Size>
array<T, Size>::array(array&& a) {
  size_ = a.size_;
  array_ = new T[size_];
  for (size_t i = ZERO; i < size_; i++) {
    array_[i] = a.array_[i];
  }
}

template <typename T, size_t Size>
array<T, Size>::~array() {
  delete[] array_;
  array_ = nullptr;
  size_ = ZERO;
}

template <typename T, size_t Size>
array<T, Size>& array<T, Size>::operator=(const array& a) {
  if (this != &a) {
    this->size_ = a.size_;
    delete[] this->array_;
    this->array_ = new T[size_];

    for (size_t i = ZERO; i < size_; i++) {
      this->array_[i] = a.array_[i];
    }
  }

  return *this;
}

template <typename T, size_t Size>
array<T, Size>& array<T, Size>::operator=(array&& a) {
  if (this != &a) {
    this->size_ = a.size_;
    delete[] this->array_;
    this->array_ = new T[size_];

    for (size_t i = ZERO; i < size_; i++) {
      this->array_[i] = a.array_[i];
    }
  }

  return *this;
}

template <typename T, size_t Size>
typename array<T, Size>::reference array<T, Size>::operator[](size_type pos) {
  return array_[pos];
}

template <typename T, size_t Size>
typename array<T, Size>::reference array<T, Size>::at(size_type pos) {
  if (pos >= size_) throw std::out_of_range("pos >= size_, choose another pos");

  return array_[pos];
}

template <typename T, size_t Size>
typename array<T, Size>::const_reference array<T, Size>::front() {
  return array_[ZERO];
}

template <typename T, size_t Size>
typename array<T, Size>::const_reference array<T, Size>::back() {
  return array_[size_ - UNIT];
}

template <typename T, size_t Size>
bool array<T, Size>::empty() {
  return (this->begin() == this->end());
}

template <typename T, size_t Size>
typename array<T, Size>::size_type array<T, Size>::size() {
  return size_;
}

template <typename T, size_t Size>
typename array<T, Size>::size_type array<T, Size>::max_size() {
  return size_;
}

template <typename T, size_t Size>
void array<T, Size>::swap(array& other) {
  std::swap(array_, other.array_);
}

template <typename T, size_t Size>
void array<T, Size>::fill(const_reference value) {
  if (this->array_ != nullptr) {
    for (size_t i = ZERO; i < this->size_; i++) {
      this->array_[i] = value;
    }
  }
}

template <typename T, size_t Size>
typename array<T, Size>::iterator array<T, Size>::data() {
  return array_;
}

template <typename T, size_t Size>
typename array<T, Size>::iterator array<T, Size>::begin() {
  return array_;
}

template <typename T, size_t Size>
typename array<T, Size>::iterator array<T, Size>::end() {
  return array_ + size_;
}

}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_2_SRC_ARRAY_S21_ARRAY_H