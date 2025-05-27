#ifndef S21_LIST_H
#define S21_LIST_H

#include <iostream>
namespace s21 {
template <typename T>
class list {
 private:
  struct Node {
    Node* prev;
    Node* next;
    T data_;
    Node(const T& d_) {
      prev = nullptr;
      next = nullptr;
      data_ = d_;
    }
  };
  Node* head_;
  Node* tail_;
  size_t size_;

 public:
  using value_type = T;
  using reference = T&;
  using const_reference = const T&;
  using size_type = size_t;
  class iterator;
  class const_iterator;

  list() : head_(nullptr), tail_(nullptr), size_(0){};
  list(size_type n) : list() {
    if (n > 0) {
      for (size_type i = 0; i < n; i++) {
        push_back(0);
      }
    }
  }
  list(std::initializer_list<value_type> const& items) : list() {
    for (auto item : items) push_back(item);
  }
  list(const list& l) : list() {
    Node* current = l.head_;
    while (current != nullptr) {
      push_back(current->data_);
      current = current->next;
    }
  }
  list(list&& l) : list() {
    swap(l);
    l.clear();
  }
  ~list() {
    clear();
    delete head_;
    delete tail_;
  }

  list& operator=(list&& l) {
    swap(l);
    l.clear();
    return *this;
  }

  const_reference front() {
    if (empty()) {
      throw std::out_of_range("Empty list");
    }
    return head_->data_;
  }
  const_reference back() {
    if (empty()) {
      throw std::out_of_range("Empty list");
    }
    return tail_->data_;
  }

  iterator begin() { return iterator(head_, this); }
  iterator end() { return iterator(nullptr, this); }
  const_iterator cbegin() { return const_iterator(head_, this); }
  const_iterator cend() { return const_iterator(nullptr, this); }

  bool empty() { return !size_; }
  size_type size() { return this->size_; }

  void clear() {
    while (!empty()) pop_back();
  }
  iterator insert(iterator pos, const_reference value) {
    Node* curr = pos.GetPtr();
    if (curr == nullptr) {
      push_back(value);
      return iterator(tail_, this);
    }
    Node* temp = new Node(value);
    if (curr == head_) {
      temp->next = head_;
      if (head_) head_->prev = temp;
      head_ = temp;
      if (!tail_) tail_ = temp;
    } else {
      temp->prev = curr->prev;
      temp->next = curr;
      if (curr->prev) curr->prev->next = temp;
      curr->prev = temp;
    }
    size_++;
    return iterator(temp, this);
  }
  void erase(iterator pos) {
    Node* temp = pos.GetPtr();
    if (temp == nullptr) return;
    if (temp == head_) {
      head_ = head_->next;
      if (head_)
        head_->prev = nullptr;
      else
        tail_ = nullptr;
    } else if (temp == tail_) {
      tail_ = tail_->prev;
      if (tail_)
        tail_->next = nullptr;
      else
        head_ = nullptr;
    } else {
      temp->prev->next = temp->next;
      temp->next->prev = temp->prev;
    }
    delete temp;
    size_--;
  }
  void push_back(const_reference value) {
    Node* temp = new Node(value);
    if (head_ == nullptr)
      head_ = tail_ = temp;
    else {
      tail_->next = temp;
      temp->prev = tail_;
      tail_ = temp;
    }
    size_++;
  }
  void pop_back() {
    if (tail_ == nullptr) return;
    Node* temp = this->tail_;
    if (tail_->prev != nullptr) {
      tail_ = tail_->prev;
      tail_->next = nullptr;
    } else {
      head_ = tail_ = nullptr;
    }
    delete temp;
    size_--;
  }
  void push_front(const_reference value) {
    Node* temp = new Node(value);
    if (this->head_ == nullptr)
      head_ = tail_ = temp;
    else {
      temp->next = head_;
      head_->prev = temp;
      head_ = temp;
    }
    size_++;
  }
  void pop_front() {
    if (this->head_ == nullptr)
      throw std::out_of_range("Cannot pop from an empty list");
    head_ = head_->next;
    if (this->head_ == nullptr)
      head_ = tail_ = nullptr;
    else {
      head_->prev = nullptr;
    }
    size_--;
  }
  void swap(list& other) {
    std::swap(this->head_, other.head_);
    std::swap(this->tail_, other.tail_);
    std::swap(this->size_, other.size_);
  }
  void merge(list& other) {
    // if(other.empty()) return;
    list current;
    Node* temp = head_;
    Node* temp2 = other.head_;
    while (temp != nullptr && temp2 != nullptr) {
      if (temp->data_ < temp2->data_) {
        current.push_back(temp->data_);
        temp = temp->next;
      } else {
        current.push_back(temp2->data_);
        temp2 = temp2->next;
      }
    }
    while (temp != nullptr) {
      current.push_back(temp->data_);
      temp = temp->next;
    }
    while (temp2 != nullptr) {
      current.push_back(temp2->data_);
      temp2 = temp2->next;
    }
    swap(current);
  }
  void splice(const_iterator pos, list& other) {
    Node* temp = const_cast<Node*>(pos.GetPtr());
    if (empty()) {
      head_ = other.head_;
      tail_ = head_;
    } else if (head_ == temp) {
      other.tail_->next = head_;
      head_->prev = other.tail_;
      head_ = other.head_;
    } else if (temp == nullptr) {
      other.head_->prev = tail_;
      tail_->next = other.head_;
      tail_ = other.tail_;
    } else {
      Node* cur = temp->prev;
      cur->next = other.head_;
      other.head_->prev = cur;
      temp->prev = other.tail_;
      other.tail_->next = temp;
    }

    size_ += other.size_;  // изменяется надо учесть
    other.head_ = other.tail_ = nullptr;
    other.size_ = 0;
  }
  void reverse() {
    if (size() == 1 || empty()) return;
    Node* temp = head_;
    Node* cur = nullptr;
    while (temp != nullptr) {
      cur = temp->prev;
      temp->prev = temp->next;
      temp->next = cur;
      temp = temp->prev;
    }
    if (cur != nullptr) {
      cur = head_;
      head_ = tail_;
      tail_ = cur;
    }
  }
  void unique() {
    if (head_ == tail_ || head_ == nullptr) return;
    Node* temp = head_;

    while (temp != nullptr && temp->next != nullptr) {
      if (temp->data_ == temp->next->data_) {
        Node* dub = temp->next;
        temp->next = dub->next;
        if (dub->next == nullptr)
          tail_ = temp;
        else
          dub->next->prev = temp;
        delete dub;
        size_--;
      } else {
        temp = temp->next;
      }
    }
  }

  void sort() {
    if (size_ < 2) return;
    bool flag_swaped;
    do {
      flag_swaped = false;
      Node* temp = head_;
      while (temp->next != nullptr) {
        if (temp->data_ > temp->next->data_) {
          std::swap(temp->data_, temp->next->data_);
          flag_swaped = true;
        }
        temp = temp->next;
      }
    } while (flag_swaped);
  }
  template <typename... Args>
  iterator insert_many(const_iterator pos, Args&&... args) {
    Node* temp = const_cast<Node*>(pos.GetPtr());
    iterator it = temp ? iterator(temp, this) : end();
    (insert(it, std::forward<Args>(args)), ...);
    return iterator(temp, this);
  }
  template <typename... Args>
  void insert_many_back(Args&&... args) {
    this->insert_many(cend(), args...);
  }
  template <typename... Args>
  void insert_many_front(Args&&... args) {
    (push_front(std::forward<Args>(args)), ...);
    // this->insert_many(cbegin(), args...);
  }
  class iterator {
   private:
    Node* ptr_;
    list* cur_;

   public:
    Node* GetPtr() { return ptr_; }
    iterator() : ptr_(nullptr), cur_(nullptr){};
    iterator(Node* ptr, list* cur) : ptr_(ptr), cur_(cur){};
    T& operator*() {
      if (!ptr_) throw std::invalid_argument("Eee");
      return ptr_->data_;
    }
    bool operator==(const iterator& other) const { return ptr_ == other.ptr_; }
    bool operator!=(const iterator& other) const { return ptr_ != other.ptr_; }
    iterator& operator++() {
      if (ptr_) ptr_ = ptr_->next;
      return *this;
    }
    iterator& operator++(int) {
      iterator temp = *this;
      ++(*this);
      return *this;
    }
    iterator& operator--() {
      if (!ptr_)
        ptr_ = cur_->tail_;
      else
        ptr_ = ptr_->prev;
      return *this;
    }
    iterator& operator--(int) {
      iterator temp = *this;
      --(*this);
      return *this;
    }
  };
  class const_iterator {
   private:
    const Node* ptr_;
    const list* cur_;

   public:
    const Node* GetPtr() const { return ptr_; }
    const_iterator() : ptr_(nullptr), cur_(nullptr){};
    const_iterator(const Node* ptr, const list* cur) : ptr_(ptr), cur_(cur){};
    const T& operator*() const {
      if (!ptr_) throw std::invalid_argument("Value is nullptr");
      return ptr_->data_;
    }
    bool operator==(const const_iterator& other) const {
      return ptr_ == other.ptr_;
    }
    bool operator!=(const const_iterator& other) const {
      return ptr_ != other.ptr_;
    }
    const_iterator& operator++() {
      if (ptr_) ptr_ = ptr_->next;
      return *this;
    }
    const_iterator& operator++(int) {
      const_iterator temp = *this;
      ++(*this);
      return *this;
    }
    const_iterator& operator--() {
      if (!ptr_)
        ptr_ = cur_->tail_;
      else
        ptr_ = ptr_->prev;
      return *this;
    }
    const_iterator& operator--(int) {
      const_iterator temp = *this;
      --(*this);
      return *this;
    }
  };
};
};  // namespace s21

#endif