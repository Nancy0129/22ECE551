#ifndef __LL_HPP__
#define __LL_HPP__

#include <assert.h>

#include <cstdlib>
#include <exception>

class Tester;

template<typename T>
class LinkedList {
 private:
  class Node {
   public:
    T data;
    Node * next;
    Node * prev;
    Node(const T & d) : data(d), next(NULL), prev(NULL) {}
    Node(const T & d, Node * n, Node * p) : data(d), next(n), prev(p) {}
  };
  Node * head;
  Node * tail;
  int size;

  Node * remove(const T & data, Node * current) {
    if (current == NULL) {
      return NULL;
    }
    if (data == current->data) {
      Node * ans = current->next;
      if (current->next == NULL) {
        tail = current->prev;
      }
      else {
        current->next->prev = current->prev;
      }
      delete current;
      size--;
      return ans;
    }
    current->next = remove(data, current->next);
    return current;
  }

 public:
  LinkedList() : head(NULL), tail(NULL), size(0) {}
  void addFront(const T & item) {
    head = new Node(item, head, NULL);
    if (tail == NULL) {
      tail = head;
    }
    else {
      head->next->prev = head;
    }
    size++;
  }
  void addBack(const T & item) {
    tail = new Node(item, NULL, tail);
    if (head == NULL) {
      head = tail;
    }
    else {
      tail->prev->next = tail;
    }
    size++;
  }
  bool remove(const T & item) {
    int pre = size;
    Node * res = remove(item, head);
    head = res;
    if (pre == size) {
      return false;
    }
    return true;
  }
  T & operator[](int index) const {
    assert(index >= 0 && index < size);
    Node * curr = head;
    for (int i = 0; i < index; i++) {
      curr = curr->next;
    }
    return curr->data;
  }
  int find(const T & item) const {
    Node * curr = head;
    int ind = 0;
    while (curr != NULL) {
      if (curr->data == item) {
        return ind;
      }
      curr = curr->next;
      ind++;
    }
    return -1;
  }
  ~LinkedList() {
    while (head != NULL) {
      Node * temp = head->next;
      delete head;
      head = temp;
    }
  }
  LinkedList(const LinkedList & rhs) : head(NULL), tail(NULL), size(0) {
    if (rhs.size > 0) {
      Node * curr = rhs.head;
      while (curr != NULL) {
        this->addBack(curr->data);
        curr = curr->next;
      }
    }
  }

  LinkedList & operator=(const LinkedList & rhs) {
    if (this != &rhs) {
      Node * h = NULL;
      Node * t = NULL;
      Node * rCurr = rhs.head;
      while (rCurr != NULL) {
        t = new Node(rCurr->data, NULL, t);
        if (h == NULL) {
          h = t;
        }
        else {
          t->prev->next = t;
        }
        rCurr = rCurr->next;
      }
      while (head != NULL) {
        Node * temp = head->next;
        delete head;
        head = temp;
      }
      head = h;
      tail = t;
      size = rhs.size;
    }
    return *this;
  }

  int getSize() const { return size; }
  friend class Tester;
};

#endif
