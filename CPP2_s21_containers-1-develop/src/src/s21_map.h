#ifndef S21_MAP_H
#define S21_MAP_H
#include <limits>

#include "Tree.h"
#include "s21_vector.h"

namespace s21 {
template <typename Key, typename T>
class map : public Tree<Key, T> {
 public:
  using key_type = Key;
  using mapped_type = T;
  using value_type = std::pair<const key_type, mapped_type>;
  using reference = value_type&;
  using const_reference = const value_type&;
  using iterator = typename Tree<Key, T>::iterator;
  using const_iterator = typename Tree<Key, T>::const_iterator;
  using size_type = size_t;
  using insert_result = std::pair<iterator, bool>;

  map() : Tree<Key, T>() {}
  map(std::initializer_list<value_type> const& items) {
    for (auto i = items.begin(); i != items.end(); ++i) {
      insert(*i);
    }
  }
  map(const map& m) : Tree<Key, T>(m) {}
  map(map&& m) : Tree<Key, T>(std::move(m)) {}
  ~map() = default;
  map& operator=(map&& m) {
    Tree<Key, T>::operator=(std::move(m));
    return *this;
  }
  T& at(const Key& key) {
    if (!contains(key)) throw std::out_of_range("Out of range");
    auto iter = Tree<Key, T>::find(key);
    return iter.curr->value_;
  }
  T& operator[](const Key& key) {
    if (!contains(key)) insert(std::make_pair(key, T()));
    auto iter = Tree<Key, T>::find(key);
    return iter.curr->value_;
  }

  iterator begin() { return Tree<Key, T>::begin(); }
  iterator end() { return Tree<Key, T>::end(); }

  bool empty() { return Tree<Key, T>::empty(); }
  size_type size() { return Tree<Key, T>::size(); }
  size_type max_size() {
    return std::numeric_limits<std::size_t>::max() / sizeof(T) / 2;
  }
  void clear() { Tree<Key, T>::clear(); }
  std::pair<iterator, bool> insert(const value_type& value) {
    return Tree<Key, T>::insert(std::make_pair(value.first, value.second));
  }
  std::pair<iterator, bool> insert(const Key& key, const T& obj) {
    return Tree<Key, T>::insert(std::make_pair(key, obj));
  }
  std::pair<iterator, bool> insert_or_assign(const Key& key, const T& obj) {
    if (!contains(key))
      return insert(key, obj);
    else {
      auto iter = Tree<Key, T>::find(key);
      erase(iter);
      auto iter2 = insert(key, obj);
      iter2.second = false;
      return iter2;
    }
  }
  void erase(iterator pos) { Tree<Key, T>::erase(pos); }
  void swap(map& other) { Tree<Key, T>::swap(other); }
  void merge(map& other) { Tree<Key, T>::merge(other); }
  bool contains(const Key& key) { return Tree<Key, T>::contains(key); }
  template <typename... Args>
  vector<insert_result> insert_many(Args&&... args) {
    vector<insert_result> results;
    (results.push_back(this->insert(std::forward<Args>(args))), ...);
    return results;
  }
};
};  // namespace s21
#endif