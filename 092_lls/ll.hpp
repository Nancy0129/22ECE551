#ifndef __LL_HPP__
#define __LL_HPP__

#include <assert.h>

#include <cstdlib>
#include <exception>
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
      return ans;
    }
    current->next = remove(data, current->next);
    return current;
  }

 public:
  LinkedList() : head(NULL), tail(NULL), size(0) {}
  void addFront(const T & item) {
    Node toAdd(item);
    if (head != NULL) {
      toAdd.next = head;
      head->prev = &toAdd;
    }
    head = &toAdd;
    if (tail == NULL) {
      tail = &toAdd;
    }
    size++;
  }
  void addBack(const T & item) {
    Node toAdd(item);
    if (tail != NULL) {
      toAdd.prev = tail;
      tail->next = &toAdd;
    }
    tail = &toAdd;
    if (head == NULL) {
      head = &toAdd;
    }
    size++;
  }
  bool remove(const T & item) {
    Node * res = remove(item, head);
    if (res == NULL) {
      return false;
    }
    head = res;
    size--;
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
  LinkedList(const LinkedList & rhs) : head(NULL), tail(NULL), size(rhs.size) {
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
      Node h(rhs.head->data);
      Node * rCurr = rhs.head->next;
      Node * tCurr = &h;
      while (rCurr != NULL) {
        Node n(rCurr->data);
        tCurr->next = &n;
        n.prev = tCurr;
        tCurr = &n;
        rCurr = rCurr->next;
      }
      while (head != NULL) {
        Node * temp = head->next;
        delete head;
        head = temp;
      }
      head = &h;
      tail = tCurr;
      size = rhs.size;
    }
    return *this;
  }

  int getSize() const { return size; }
};

#endif
