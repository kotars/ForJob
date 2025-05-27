#ifndef S21_SET_H
#define S21_SET_H

#include <iostream>
#include <limits>

#include "Tree.h"
#include "s21_vector.h"
namespace s21 {
template <typename Key>
class set : public Tree<Key, Key> {
 public:
  using key_type = Key;
  using size_type = size_t;
  using value_type = Key;
  using reference = Key &;
  using const_reference = const Key &;
  using iterator = typename Tree<Key, Key>::iterator;
  using const_iterator = typename Tree<Key, Key>::const_iterator;
  using insert_result = std::pair<iterator, bool>;

  set() : Tree<Key, Key>() {}
  set(std::initializer_list<value_type> const &items) {
    for (auto i = items.begin(); i != items.end(); ++i) {
      insert(*i);
    }
  }
  set(const set &s) : Tree<Key, Key>(s) {}
  set(set &&s) : Tree<Key, Key>(std::move(s)) {}
  ~set() = default;

  set &operator=(set &&s) noexcept;
  set &operator=(const set &s);
  size_type max_size() {
    return (std::numeric_limits<size_type>::max() / sizeof(Key) / 2);
  }
  void clear() {
    for (auto it = set::begin(); it != set::end();
         ++it) {  // перебор всех элементов
      set::erase(it);
    }
  }
  std::pair<iterator, bool> insert(const value_type &value) {
    return Tree<Key, Key>::insert(
        std::make_pair(value, value));  // Вставка с дублированием ключа
  };

  iterator find(const key_type &key) { return Tree<Key, Key>::find(key); }
  template <typename... Args>
  vector<insert_result> insert_many(Args &&...args) {
    vector<insert_result> results;
    (results.push_back(this->insert(std::forward<Args>(args))), ...);
    return results;
  }
};
};  // namespace s21

#endif