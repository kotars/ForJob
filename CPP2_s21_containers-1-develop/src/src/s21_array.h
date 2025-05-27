#ifndef S21_ARRAY_H
#define S21_ARRAY_H

#include <iostream>

namespace s21 {
template <typename T, std::size_t N>
class array {
 private:
  size_t size_ = N;
  T data_[N];

 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = T *;
  using const_iterator = const T *;
  using size_type = size_t;
  array() : size_(N), data_{} {}
  array(std::initializer_list<value_type> const &items) : array() {
    for (size_type i = 0; i < size_; i++) data_[i] = *(items.begin() + i);
  }
  array(const array &a) : array() {
    for (size_type i = 0; i < size_; i++) data_[i] = a.data_[i];
  }
  array(array &&a) : array(a) {}
  ~array() {}
  array &operator=(array &&a) {
    if (this != &a) {
      for (size_type i = 0; i < size_; i++) data_[i] = a.data_[i];
    }
    return *this;
  }

  reference at(size_type pos) {
    if (pos >= size_) throw std::out_of_range("Out of range");
    return data_[pos];
  }
  reference operator[](size_type pos) { return data_[pos]; }
  const_reference front() { return data_[0]; }
  const_reference back() { return data_[size_ - 1]; }
  iterator data() { return data_; }
  iterator begin() { return data_; }
  iterator end() { return data_ + size_; }
  bool empty() { return !size_; }
  size_type size() { return size_; }
  size_type max_size();
  void swap(array &other) {
    std::swap(data_, other.data_);
    std::swap(size_, other.size_);
  }
  void fill(const_reference value) {
    for (size_type i = 0; i < size_; i++) data_[i] = value;
  }
};
};  // namespace s21
#endif