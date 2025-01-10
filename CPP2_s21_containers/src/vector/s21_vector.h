#ifndef CPP2_S21_CONTAINERS_2_SRC_VECTOR_VECTOR_H
#define CPP2_S21_CONTAINERS_2_SRC_VECTOR_VECTOR_H

#include <initializer_list>
#include <iostream>
#include <limits>
#include <utility>

namespace s21 {
template <typename T>
class vector {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = T *;
  using const_iterator = const T *;
  using size_type = size_t;

  vector();
  explicit vector(size_type n);
  vector(std::initializer_list<value_type> const &items);
  vector(const vector &v);
  vector(vector &&v) noexcept;
  ~vector();

  vector<T> &operator=(const vector &v);
  vector<T> &operator=(vector &&v) noexcept;

  reference at(size_type pos);
  const_reference at(size_type pos) const;
  reference operator[](size_type pos);
  const_reference operator[](size_type pos) const;
  reference front();
  const_reference front() const;
  reference back();
  const_reference back() const;
  iterator data();
  const_iterator data() const;

  iterator begin();
  iterator cbegin() const;
  iterator end();
  iterator cend() const;

  bool empty() const;
  size_type size() const;
  size_type max_size() const;
  void reserve(size_type size);
  size_type capacity() const;
  void shrink_to_fit();

  void clear();
  iterator insert(const_iterator pos, const_reference value);
  iterator erase(const_iterator pos);
  void push_back(const_reference value);
  void pop_back();
  void swap(vector &other);

  template <typename... Args>
  iterator insert_many(const_iterator pos, Args &&...args);
  template <typename... Args>
  void insert_many_back(Args &&...args);

 private:
  size_t size_ = 0;
  size_t capacity_ = 0;
  value_type *vector_ = nullptr;

 private:
};

template <typename T>
vector<T>::vector() : size_(0U), capacity_(0U), vector_(nullptr) {}

template <typename T>
vector<T>::vector(size_type n)
    : size_(n), capacity_(n), vector_(n ? new value_type[n] : nullptr) {}

template <class T>
vector<T>::vector(std::initializer_list<value_type> const &items) {
  vector_ = new value_type[items.size()];
  int i = 0;
  for (auto it = items.begin(); it != items.end(); it++) {
    vector_[i] = *it;
    i++;
  }
  size_ = items.size();
  capacity_ = items.size();
}

template <typename T>
vector<T>::vector(const vector &v) : vector(v.size()) {
  //  size_ = v.size_;
  //  capacity_ = v.capacity_;
  std::copy(v.cbegin(), v.cend(), begin());
}

template <typename T>
vector<T>::vector(vector &&v) noexcept {
  size_ = std::exchange(v.size_, 0);
  capacity_ = std::exchange(v.capacity_, 0);
  vector_ = std::exchange(v.vector_, nullptr);
}

template <typename T>
vector<T>::~vector() {
  delete[] vector_;
  vector_ = nullptr;
  size_ = 0;
  capacity_ = 0;
}

template <typename T>
vector<T> &vector<T>::operator=(const vector &v) {
  if (this != &v) {
    delete[] vector_;
    size_ = 0;
    capacity_ = 0;
    size_ = v.size_;
    capacity_ = v.capacity_;
    vector_ = v.vector_ ? new T[v.size_] : nullptr;
    size_ = v.size_;
    capacity_ = v.capacity_;
    std::copy(v.cbegin(), v.cend(), begin());
  }
  return *this;
}

template <typename T>
vector<T> &vector<T>::operator=(vector &&v) noexcept {
  if (this != &v) {
    delete[] vector_;
    size_ = v.size_;
    capacity_ = v.capacity_;
    vector_ = v.vector_;
    v.size_ = 0;
    v.capacity_ = 0;
    v.vector_ = nullptr;
  }
  return *this;
}

template <typename T>
typename vector<T>::reference vector<T>::at(size_type pos) {
  if (pos >= size_) {
    throw std::out_of_range("Out of range");
  }
  return vector_[pos];
}

template <typename T>
typename vector<T>::const_reference vector<T>::at(size_type pos) const {
  if (pos >= size_) {
    throw std::exception();
  }
  return vector_[pos];
}

template <typename T>
typename vector<T>::reference vector<T>::operator[](size_type pos) {
  return vector_[pos];
}

template <typename T>
typename vector<T>::const_reference vector<T>::operator[](size_type pos) const {
  return vector_[pos];
}

template <typename T>
typename vector<T>::reference vector<T>::front() {
  return vector_[0];
}

template <typename T>
typename vector<T>::const_reference vector<T>::front() const {
  return vector_[0];
}

template <typename T>
typename vector<T>::reference vector<T>::back() {
  return vector_[size_ - 1];
}

template <typename T>
typename vector<T>::const_reference vector<T>::back() const {
  return vector_[size_ - 1];
}

template <typename T>
typename vector<T>::iterator vector<T>::data() {
  return vector_;
}

template <typename T>
typename vector<T>::iterator vector<T>::begin() {
  return vector_;
}

template <typename T>
typename vector<T>::iterator vector<T>::cbegin() const {
  return vector_;
}

template <typename T>
typename vector<T>::iterator vector<T>::end() {
  return vector_ + size_;
}

template <typename T>
typename vector<T>::iterator vector<T>::cend() const {
  return vector_ + size_;
}

template <typename T>
bool vector<T>::empty() const {
  return size_ == 0;
}

template <typename T>
typename vector<T>::size_type vector<T>::size() const {
  return size_;
}

template <typename T>
typename vector<T>::size_type vector<T>::max_size() const {
  return std::numeric_limits<size_type>::max() / sizeof(value_type) / 2;
}

template <typename T>
void vector<T>::reserve(size_type size) {
  if (size > max_size()) {
    throw std::exception();
  }
  if (size >= capacity_) {
    iterator temp = new value_type[size];
    std::copy(begin(), end(), temp);
    if (vector_ != nullptr) delete[] vector_;
    vector_ = temp;
    capacity_ = size;
  }
}

template <typename T>
typename vector<T>::size_type vector<T>::capacity() const {
  return capacity_;
}

template <typename T>
void vector<T>::shrink_to_fit() {
  if (capacity_ > size_) {
    capacity_ = size_;
    value_type *tmp = vector_;
    vector_ = new value_type[capacity_];
    for (size_t i = 0; i < size_; i++) {
      vector_[i] = tmp[i];
    }
    delete[] tmp;
  }
}

template <typename T>
void vector<T>::clear() {
  size_ = 0;
  capacity_ = 0;
}

template <typename T>
typename vector<T>::iterator vector<T>::insert(const_iterator pos,
                                               const_reference value) {
  const size_type index = pos - cbegin();
  if (size_ == capacity_) {
    reserve(capacity_ ? capacity_ * 2 : 1);
  }

  std::copy(begin() + index, end(), vector_ + index + 1);
  vector_[index] = value;
  size_++;
  return begin() + index;
}

template <typename T>
typename vector<T>::iterator vector<T>::erase(const_iterator pos) {
  const size_type index = pos - begin();
  std::move(begin() + index + 1, end(), vector_ + index);
  --size_;
  return begin() + index;
}

template <typename T>
void vector<T>::push_back(const_reference value) {
  if (size_ == capacity_) {
    reserve(capacity_ ? capacity_ * 2 : 1);
  }
  ++size_;
  vector_[size_ - 1] = value;
}

template <typename T>
void vector<T>::pop_back() {
  if (size_ != 0) {
    --size_;
  }
}

template <typename T>
void vector<T>::swap(vector &other) {
  std::swap(vector_, other.vector_);
  std::swap(size_, other.size_);
  std::swap(capacity_, other.capacity_);
}

template <typename value_type>
template <typename... Args>
typename vector<value_type>::iterator vector<value_type>::insert_many(
    const_iterator pos, Args &&...args) {
  vector<value_type> temp{args...};
  iterator it = begin() + (pos - cbegin());
  for (size_t i = 0; i < temp.size(); ++i) {
    it = insert(it, temp[i]);
    ++it;
  }
  return it;
}

template <typename value_type>
template <typename... Args>
void vector<value_type>::insert_many_back(Args &&...args) {
  insert_many(end(), args...);
}

}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_2_SRC_VECTOR_VECTOR_H
