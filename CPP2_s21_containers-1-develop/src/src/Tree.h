#ifndef TREE_H
#define TREE_H
#include <iostream>

namespace s21 {
template <typename Key, typename T>
class Tree {
 public:
  class TreeIterator;
  class TreeConstIterator;
  using key_type = Key;
  using mapped_type = T;
  using value_type = std::pair<const key_type, mapped_type>;
  using reference = mapped_type &;
  using const_reference = const mapped_type &;
  using iterator = TreeIterator;
  using const_iterator = TreeConstIterator;
  using size_type = size_t;

 private:
  struct Node {
    key_type key_;
    mapped_type value_;
    Node *left_;
    Node *right_;
    Node *parent_;  // добавить обработку parent в insert, clear, remove
    Node(key_type k, mapped_type val, Node *par = nullptr) {
      key_ = k;
      value_ = val;
      parent_ = par;
      left_ = right_ = nullptr;
    }
  };
  Node *root_;
  Node *GetMin_(Node *parent) {
    if (parent->left_ != nullptr) return GetMin_(parent->left_);
    return parent;
  }
  Node *Insert_(Node *parent, key_type key, mapped_type value) {
    if (parent == nullptr) return new Node(key, value);
    if (parent->key_ > key) {
      parent->left_ = Insert_(parent->left_, key, value);
      parent->left_->parent_ = parent;
    } else if (parent->key_ < key) {
      parent->right_ = Insert_(parent->right_, key, value);
      parent->right_->parent_ = parent;
    }
    return parent;
  }
  Node *CopyNode_(Node *node, Node *parent) {
    // std::cout << parent->key_<<"\n";
    if (node == nullptr) return nullptr;
    Node *new_node = new Node(node->key_, node->value_, parent);
    new_node->left_ = CopyNode_(node->left_, new_node);
    new_node->right_ = CopyNode_(node->right_, new_node);
    return new_node;
  }
  Node *FindNode_(Node *parent, key_type key) {
    if (parent == nullptr) return nullptr;
    if (parent->key_ == key) return parent;
    if (parent->key_ < key)
      return FindNode_(parent->right_, key);
    else if (parent->key_ > key)
      return FindNode_(parent->left_, key);
    else
      return nullptr;
  }
  void ClearTree(Node *parent) {
    if (parent == nullptr) return;
    ClearTree(parent->left_);
    ClearTree(parent->right_);
    delete parent;
  }
  size_type CountElem_(Node *parent) {
    return parent == nullptr
               ? 0
               : 1 + CountElem_(parent->left_) + CountElem_(parent->right_);
  }
  Node *DeleteNode_(Node *parent, key_type key) {
    if (!parent) return nullptr;
    if (parent->key_ > key)
      parent->left_ = DeleteNode_(parent->left_, key);
    else if (parent->key_ < key)
      parent->right_ = DeleteNode_(parent->right_, key);
    else {
      if (parent->left_ == nullptr) {
        Node *temp = parent->right_;
        delete parent;
        return temp;
      } else if (parent->right_ == nullptr) {
        Node *temp = parent->left_;
        delete parent;
        return temp;
      } else {
        Node *temp = GetMin_(parent->right_);
        parent->key_ = temp->key_;
        parent->right_ = DeleteNode_(parent->right_, temp->key_);
      }
    }
    return parent;
  }

 public:
  Tree() : root_(nullptr) {}
  Tree(std::initializer_list<value_type> const &items) : Tree() {
    for (auto item : items) insert(item);
  }
  Tree(const Tree &tr) : Tree() { this->root_ = CopyNode_(tr.root_, nullptr); }
  Tree(Tree &&other) : Tree(other) {}
  ~Tree() { ClearTree(root_); }
  Tree &operator=(Tree &&tr) {
    swap(tr);
    tr.clear();
    return *this;
  };
  iterator begin() { return TreeIterator(GetMin_(root_)); }
  iterator end() { return TreeIterator(nullptr); }
  const_iterator cbegin() { return TreeConstIterator(GetMin_(root_)); }
  const_iterator cend() { return TreeConstIterator(nullptr); }
  bool empty() { return root_ == nullptr; }
  size_type size() { return CountElem_(root_); }
  std::pair<iterator, bool> insert(const value_type &value) {
    bool ok = !contains(value.first);
    iterator i = find(value.first);
    if (ok) {
      root_ = Insert_(root_, value.first, value.second);
      i = iterator(find(value.first));
    }
    return std::make_pair(i, ok);
  };
  iterator find(const key_type &key) { return iterator(FindNode_(root_, key)); }
  void clear() { ClearTree(root_); }
  void swap(Tree &other) { std::swap(root_, other.root_); }
  void erase(iterator pos) {
    Node *posNode = pos.GetPtr();
    DeleteNode_(root_, posNode->key_);
  }
  bool contains(const key_type &key) {
    return FindNode_(root_, key) != nullptr;
  }
  void merge(Tree &other) {
    for (auto i = other.begin(); i != other.end(); ++i) {
      insert(std::make_pair(i.curr->key_, i.curr->value_));
    }
    other.clear();
  }
  class TreeIterator {
   public:
    Node *curr;
    Node *GetPtr() { return this->curr; }
    TreeIterator() { curr = nullptr; }
    TreeIterator(Node *parent) { curr = parent; }
    iterator &operator++() {
      Node *p;
      if (curr->right_ != nullptr) {
        curr = curr->right_;
        while (curr->left_ != nullptr) curr = curr->left_;
      } else {
        p = curr->parent_;
        while (p != nullptr && curr == p->right_) {
          curr = p;
          p = p->parent_;
        }
        curr = p;
      }
      return *this;
    }
    iterator &operator++(int) {
      iterator temp = *this;
      ++(*this);
      return *this;
    }
    Key &operator*() { return curr->key_; }
    bool operator==(const iterator &other) const { return other.curr == curr; }
    bool operator!=(const iterator &other) const { return other.curr != curr; }
    iterator &operator--() {
      Node *p;
      if (curr->left_ != nullptr) {
        curr = curr->left_;
        while (curr->right_ != nullptr) curr = curr->right_;
      } else {
        p = curr->parent_;
        while (p != nullptr && curr == p->left_) {
          curr = p;
          p = p->parent_;
        }
        curr = p;
      }
      return *this;
    }
    iterator &operator--(int) {
      iterator temp = *this;
      --(*this);
      return *this;
    }
  };
  class TreeConstIterator {
   public:
    Node *curr;
    Node *GetPtr() { return this->curr; }
    TreeConstIterator() { curr = nullptr; }
    TreeConstIterator(Node *parent) { curr = parent; }
    const_iterator &operator++() {
      Node *p;
      if (curr->right_ != nullptr) {
        curr = curr->right_;
        while (curr->left_ != nullptr) curr = curr->left_;
      } else {
        p = curr->parent_;
        while (p != nullptr && curr == p->right_) {
          curr = p;
          p = p->parent_;
        }
        curr = p;
      }
      return *this;
    }
    const_iterator &operator++(int) {
      const_iterator temp = *this;
      ++(*this);
      return *this;
    }
    Key &operator*() { return curr->key_; }
    bool operator==(const const_iterator &other) const {
      return other.curr == curr;
    }
    bool operator!=(const const_iterator &other) const {
      return other.curr != curr;
    }
    const_iterator &operator--() {
      Node *p;
      if (curr->left_ != nullptr) {
        curr = curr->left_;
        while (curr->right_ != nullptr) curr = curr->right_;
      } else {
        p = curr->parent_;
        while (p != nullptr && curr == p->left_) {
          curr = p;
          p = p->parent_;
        }
        curr = p;
      }
      return *this;
    }
    const_iterator &operator--(int) {
      const_iterator temp = *this;
      --(*this);
      return *this;
    }
  };
};
};  // namespace s21
// iter++; // key = 2
// iter++; // key = 3
// iter++; // key = 4
// и тд
// сначала левая ветвь, потом правая ветвь, поднять на уровень ближе к корню.
#endif