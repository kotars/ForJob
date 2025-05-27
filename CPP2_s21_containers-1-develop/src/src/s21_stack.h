#ifndef S21_STACK_H
#define S21_STACK_H

#include <iostream>

#include "s21_list.h"

namespace s21 {
template <typename T, class Container = s21::list<T>>
class stack {
 private:
  Container cont;

 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = size_t;
  stack() : cont() {}
  stack(std::initializer_list<value_type> const &items) : cont(items) {}
  stack(const stack &s) : cont(s.cont) {}
  stack(stack &&s) : cont(std::move(s.cont)) {}
  ~stack() {}
  stack &operator=(stack &&s) {
    this->cont = std::move(s.cont);
    return *this;
  }
  const_reference top() {
    if (empty()) throw std::logic_error("AAAAAA");
    return cont.back();
  }
  bool empty() { return cont.empty(); }
  size_type size() { return cont.size(); }
  void push(const_reference value) { cont.push_back(value); }
  void pop() {
    if (empty()) throw std::logic_error("AAAAAA");
    cont.pop_back();
  }
  void swap(stack &other) { cont.swap(other.cont); }
  template <typename... Args>
  void insert_many_front(Args &&...args) {
    cont.insert_many_front(args...);
  }
};
};  // namespace s21

#endif