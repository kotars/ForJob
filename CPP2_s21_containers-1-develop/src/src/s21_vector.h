#ifndef S21_VECTOR_H
#define S21_VECTOR_H

#include <iostream>
#include <limits>

// добавить insert_many
namespace s21 {
template <class T>
class vector {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = T *;
  using const_iterator = const T *;
  using size_type = size_t;

 private:
  size_type size_{};
  size_type capacity_{};
  T *data_{nullptr};
  void reserve_more_capacity(size_t size) {
    if (size >= capacity_) {
      value_type *buff = new value_type[size];
      for (size_t i = 0; i < size_; ++i) buff[i] = std::move(data_[i]);
      delete[] data_;
      data_ = buff;
      capacity_ = size;
    }
  }

 public:
  vector() : size_(0), capacity_(0), data_(nullptr){};
  vector(size_type n) : vector() {
    if (n <= 0) throw std::invalid_argument("Allocating size must be non zero");
    this->size_ = n;
    this->capacity_ = n;
    this->data_ = new value_type[n];
    for (size_type i = 0; i < n; i++) data_[i] = 0;
  }
  vector(std::initializer_list<value_type> const &items)
      : vector(items.size()) {
    size_type i = 0;
    for (const auto &item : items) this->data_[i++] = item;
  }
  vector(const vector &v) : vector() {
    if (v.size_ == 0)
      throw std::invalid_argument("Allocating size must be non zero");
    this->size_ = v.size_;
    this->capacity_ = v.capacity_;

    if (this->data_) throw std::logic_error("this->data_ is not nullptr");

    this->data_ = new value_type[this->size_];
    for (size_type i = 0; i < this->size_; i++) this->data_[i] = v.data_[i];
  }
  vector(vector &&v) : vector() {
    this->size_ = v.size_;
    this->capacity_ = v.capacity_;
    this->data_ = v.data_;
    v.size_ = 0;
    v.capacity_ = 0;
    delete v.data_;
    v.data_ = nullptr;
  }
  ~vector() {
    delete[] this->data_;
    this->data_ = nullptr;
  }

  void operator=(vector &&v) {
    if (&v != this) {
      delete[] this->data_;
      this->data_ = nullptr;
      this->size_ = v.size_;
      this->capacity_ = v.capacity_;
      this->data_ = v.data_;

      v.data_ = nullptr;
      v.size_ = 0;
      v.capacity_ = 0;
    }
  }

  reference at(size_type pos) {
    if (pos >= this->size_ || this->data_ == nullptr)
      throw std::out_of_range("pos out of range");
    return *(this->data_ + pos);
  }
  reference operator[](size_type pos) {
    if (pos >= this->size_ || this->data_ == nullptr)
      throw std::out_of_range("pos out of range");
    return *(this->data_ + pos);
  }
  const_reference front() {
    if (empty()) throw std::invalid_argument("Data is nullptr");
    return data_[0];
  }
  const_reference back() {
    if (this->data_ == nullptr) throw std::invalid_argument("Data is nullptr");
    return data_[this->size_ - 1];
  }
  T *data() { return this->data_; }

  iterator begin() { return this->data_; }
  iterator end() { return this->data_ + this->size_; }
  bool empty() { return !this->size_; }
  size_type size() { return this->size_; }
  size_type max_size() {
    return std::numeric_limits<std::size_t>::max() / sizeof(T) / 2;
  }
  void reserve(size_type size) { reserve_more_capacity(size); }
  size_type capacity() { return this->capacity_; }
  void shrink_to_fit() {
    if (this->capacity_ == this->size_) return;
    if (this->size_ == 0)
      throw std::invalid_argument("Allocating size must be non zero");
    value_type *temp = new value_type[this->size_];
    for (size_type i = 0; i < this->size_; i++) temp[i] = this->data_[i];
    delete[] data_;
    this->data_ = temp;
    this->capacity_ = this->size_;
  }

  void clear() {
    delete[] data_;
    this->data_ = nullptr;
    this->size_ = 0;
  }
  iterator insert(iterator pos, const_reference value) {
    size_type pos_id = 0;
    for (size_type i = 0; i < this->size_; i++) {
      if (*(this->data_ + i) == *pos) {
        pos_id = i;
        break;
      }
    }
    if (pos == end()) {
      push_back(value);
    } else if (pos == begin() || pos_id < size_) {
      reserve_more_capacity(size_ + 1);
      value_type *temp = new value_type[size_ + 1];
      for (size_type i = 0; i < pos_id; i++) temp[i] = data_[i];
      temp[pos_id] = value;
      for (size_type i = pos_id + 1; i < size_ + 1; i++) temp[i] = data_[i - 1];
      delete[] data_;
      data_ = temp;
      size_++;
    }
    return begin() + pos_id;
  }

  void erase(iterator pos) {
    size_type pos_id = 0;
    for (size_type i = 0; i < this->size_; i++) {
      if (*(this->data_ + i) == *pos) {
        pos_id = i;
        break;
      }
      // std::cout << *this->data_+i << " " << *pos << " " << *this->begin()<<
      // "\n";
    }
    for (size_type i = pos_id; i < this->size_ - 1; i++)
      this->data_[i] = this->data_[i + 1];
    this->size_ -= 1;
  }
  void push_back(const_reference value) {
    reserve_more_capacity(this->size_ + 1);
    value_type *temp = new value_type[this->size() + 1];
    for (size_type i = 0; i < this->size_; i++) temp[i] = data_[i];
    temp[this->size_] = value;
    delete[] this->data_;
    this->data_ = nullptr;
    this->data_ = temp;
    this->size_ += 1;
  }
  void pop_back() {
    value_type *temp = new value_type[this->size() - 1];
    for (size_type i = 0; i < this->size_ - 1; i++) temp[i] = data_[i];
    delete[] this->data_;
    this->data_ = nullptr;
    this->data_ = temp;
    this->size_ -= 1;
  }
  void swap(vector &other) {
    std::swap(this->data_, other.data_);
    std::swap(this->size_, other.size_);
    std::swap(this->capacity_, other.capacity_);
  }
};
};  // namespace s21
#endif
