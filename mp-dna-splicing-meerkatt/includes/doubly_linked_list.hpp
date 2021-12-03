#ifndef DOUBLYLINKEDLIST_H
#define DOUBLYLINKEDLIST_H

#include <cstdlib>  // provides definition for size_t, the maximum size of a theoretically possible object of any type
#include <iomanip>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

#include "node.hpp"
#include "stdexcept"

using std::endl;
using std::ostream;
using std::ostringstream;
using std::setfill;
using std::setw;
using std::string;

class ValueNotFound {};
class ListEmpty {};

// template class definition for doubly linked list
// ...
template <typename T>
class DoublyLinkedList {
public:
  DoublyLinkedList() = default;
  DoublyLinkedList(T val);
  explicit DoublyLinkedList(const std::vector<T>& values);
  DoublyLinkedList(const DoublyLinkedList& rhs);
  DoublyLinkedList& operator=(const DoublyLinkedList& rhs);
  virtual ~DoublyLinkedList();

  Node<T>* getHead() const;
  Node<T>* getTail() const;
  void setHead(Node<T>* head);
  void setTail(Node<T>* tail);
  void setSize(size_t size);
  T& back();
  T& front();
  void pop_back();
  void pop_front();

  void push_back(T val);
  void push_front(T val);

  void insert_at(size_t idx, T val);
  void erase_at(size_t idx);

  T& find(T val);
  void clear();

  size_t size() const { return size_; }
  bool empty() const { return (head_ == nullptr); };

  friend std::ostream& operator<<(
      std::ostream& os,
      const DoublyLinkedList& ll);  // friend b/c we don't have iterators yet!

protected:
  Node<T>* head_ = nullptr;
  Node<T>* tail_ = nullptr;
  size_t size_ = 0;
};

template <typename T>
DoublyLinkedList<T>::DoublyLinkedList(T val) {
  Node<T>* first = new Node(val);
  head_ = tail_ = first;
  ++size_;
}

template <typename T>
DoublyLinkedList<T>::DoublyLinkedList(const std::vector<T>& values) {
  if (values.size() <= 0) {
    size_ = 0;
    head_ = nullptr;
    tail_ = nullptr;
    return;
  }
  Node<T>* curr = new Node(values.at(0));
  head_ = curr;
  ++size_;

  for (size_t idx = 1; idx < values.size(); ++idx) {
    Node<T>* temp = new Node(values.at(idx));
    curr->next = temp;
    curr->next->prev = curr;
    ++size_;
    curr = curr->next;
  }
  tail_ = curr;
}

template <typename T>
DoublyLinkedList<T>::DoublyLinkedList(const DoublyLinkedList& rhs) {
  if (rhs.getHead() == nullptr) {
    size_ = 0;
    head_ = nullptr;
    tail_ = nullptr;
    return;
  }
  Node<T>* curr = new Node(rhs.getHead()->data);
  Node<T>* rhs_temp = rhs.getHead()->next;
  head_ = curr;
  ++size_;

  for (size_t idx = 1; idx < rhs.size(); ++idx) {
    Node<T>* temp = new Node(rhs_temp->data);
    curr->next = temp;
    curr->next->prev = curr;
    ++size_;
    curr = curr->next;
    rhs_temp = rhs_temp->next;
  }
  tail_ = curr;
}

template <typename T>
DoublyLinkedList<T>::~DoublyLinkedList() {
  clear();
}

template <typename T>
void DoublyLinkedList<T>::push_back(T val) {
  Node<T>* temp = new Node(val);
  if (tail_ == nullptr) {
    tail_ = head_ = temp;
    ++size_;
    return;
  }
  tail_->next = temp;
  temp->prev = tail_;
  tail_ = temp;
  ++size_;
}

template <typename T>
void DoublyLinkedList<T>::push_front(T val) {
  Node<T>* temp = new Node(val);
  if (head_ == nullptr) {
    head_ = tail_ = temp;
    ++size_;
    return;
  }
  head_->prev = temp;
  temp->next = head_;
  head_ = temp;
  ++size_;
}

template <typename T>
void DoublyLinkedList<T>::pop_back() {
  if (head_ == nullptr) {
    throw std::runtime_error("empty list");
  }
  if (tail_->prev == nullptr) {
    delete tail_;
    head_ = tail_ = nullptr;
    --size_;
    return;
  }
  Node<T>* curr = tail_->prev;
  delete tail_;
  curr->next = nullptr;
  tail_ = curr;
  --size_;
}

template <typename T>
void DoublyLinkedList<T>::pop_front() {
  if (head_ == nullptr) {
    throw std::runtime_error("empty list");
  }
  if (head_->next == nullptr) {
    delete head_;
    head_ = tail_ = nullptr;
    --size_;
    return;
  }
  Node<T>* curr = head_->next;
  delete head_;
  curr->prev = nullptr;
  head_ = curr;
  --size_;
}

template <typename T>
void DoublyLinkedList<T>::clear() {
  if (head_ == nullptr) {
    return;
  }
  while (head_ != tail_) {
    pop_front();
  }
  pop_front();
}

template <typename T>
T& DoublyLinkedList<T>::find(T val) {
  if (head_ == nullptr) {
    throw std::runtime_error("Not Found");
  }
  Node<T>* curr = head_;
  while (curr->data != val) {
    if (curr->next == nullptr || curr == nullptr) {
      throw std::runtime_error("Not Found");
    }
    curr = curr->next;
  }
  T& c = curr->data;
  return c;
}

template <typename T>
void DoublyLinkedList<T>::insert_at(size_t idx, T val) {
  if (idx > size_) {
    throw std::runtime_error("invalid index");
  } else if (idx == size_) {
    push_back(val);
    return;
  } else if (idx == 0) {
    push_front(val);
    return;
  }
  size_t count = 1;
  Node<T>* curr = head_;
  while (count < idx) {
    curr = curr->next;
    ++count;
  }
  Node<T>* temp = curr->next;
  curr->next = new Node(val);
  curr->next->prev = curr;
  curr = curr->next;
  curr->next = temp;
  temp->prev = curr;
  ++size_;
}
template <typename T>
void DoublyLinkedList<T>::erase_at(size_t idx) {
  if (idx >= size_) {
    throw std::runtime_error("invalid index");
  } else if (idx == size_ - 1) {
    pop_back();
    return;
  } else if (idx == 0) {
    pop_front();
    return;
  }
  size_t count = 1;
  Node<T>* curr = head_;
  while (count < idx) {
    curr = curr->next;
    ++count;
  }
  Node<T>* temp = curr->next;
  curr->next = temp->next;
  temp->next->prev = curr;
  delete temp;
  temp = nullptr;
  --size_;
}

template <typename T>
T& DoublyLinkedList<T>::back() {
  if (tail_ == nullptr) {
    throw std::runtime_error("Not Found");
  }
  T& c = tail_->data;
  return c;
}
template <typename T>
T& DoublyLinkedList<T>::front() {
  if (head_ == nullptr) {
    throw std::runtime_error("Not Found");
  }
  T& c = head_->data;
  return c;
}

template <typename T>
Node<T>* DoublyLinkedList<T>::getHead() const {
  return head_;
}

template <typename T>
Node<T>* DoublyLinkedList<T>::getTail() const {
  return tail_;
}

template <typename T>
void DoublyLinkedList<T>::setHead(Node<T>* head) {
  head_ = head;
}

template <typename T>
void DoublyLinkedList<T>::setTail(Node<T>* tail) {
  tail_ = tail;
}
template <typename T>
void DoublyLinkedList<T>::setSize(size_t size) {
  size_ = size;
}

template <typename T>
DoublyLinkedList<T>& DoublyLinkedList<T>::operator=(
    const DoublyLinkedList& rhs) {
  if (this->head_ == rhs.getHead()) {
    return *this;
  }

  clear();
  if (rhs.empty()) {
    return *this;
  }
  Node<T>* curr = rhs.getHead();

  while (curr->next) {
    this->push_back(curr->data);
    curr = curr->next;
  }
  this->push_back(curr->data);
  return *this;
}
// for template instantiation
// template function definitions

#endif