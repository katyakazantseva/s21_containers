#ifndef CPP2_S21_CONTAINERS_2_SRC_STACK_S21_STACK_H_
#define CPP2_S21_CONTAINERS_2_SRC_STACK_S21_STACK_H_

#include "../list/s21_list.h"

namespace s21 {

template <class T, class Container = s21::list<T>>
class stack {
 public:
  using contsainer_type = Container;
  using value_type = T;
  using reference = typename Container::reference;
  using const_reference = typename Container::const_reference;
  using size_type = typename Container::size_type;

  stack() = default;
  stack(std::initializer_list<value_type> const &items) {
    for (auto &i : items) {
      push(i);
    }
  }

  stack(const stack &other) : stack_(other.stack_) {}
  stack(stack &&other) : stack_(std::move(other.stack_)) {}

  stack &operator=(stack &&other) noexcept {
    if (this != &other) stack_ = std::move(other.stack_);
    return *this;
  }
  stack &operator=(const stack &other) {
    if (this != &other) stack_ = other.stack_;
    return *this;
  }

  ~stack() = default;

  /* Element access */
  const_reference top() { return stack_.front(); }

  /* Capacity */
  bool empty() { return stack_.empty(); }

  size_type size() { return stack_.size(); }

  /* Modifiers */

  void push(const_reference value) { return stack_.push_front(value); }

  void pop() { return stack_.pop_front(); }

  void swap(stack &other) { return stack_.swap(other.stack_); }

 protected:
  Container stack_;
};

}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_2_SRC_STACK_S21_STACK_H_