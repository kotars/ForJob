#ifndef S21_QUEUE_H
#define S21_QUEUE_H

#include <iostream>

#include "s21_list.h"
namespace s21 {
template <typename T, class Container = s21::list<T>>
class queue {
 private:
  Container cont;

 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = size_t;
  queue() : cont() {}
  queue(std::initializer_list<value_type> const &items) : cont(items) {}
  queue(const queue &q) : cont(q.cont) {}
  queue(queue &&q) : cont(std::move(q.cont)) {}
  ~queue() {}
  queue &operator=(queue &&q) {
    this->cont = std::move(q.cont);
    return *this;
  }
  const_reference front() {
    if (empty()) throw std::logic_error("AAAAAA");
    return cont.front();
  }
  const_reference back() { return cont.back(); }
  bool empty() { return cont.empty(); }
  size_type size() { return cont.size(); }

  void push(const_reference value) { cont.push_back(value); }
  void pop() { this->cont.pop_front(); }
  void swap(queue &other) { cont.swap(other.cont); }
  template <typename... Args>
  void insert_many_back(Args &&...args) {
    cont.insert_many_back(args...);
  }
};
}  // namespace s21

#endif