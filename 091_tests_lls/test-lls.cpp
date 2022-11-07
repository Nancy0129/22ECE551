#include <assert.h>

#include <cstdlib>
#include <iostream>

#include "il.hpp"

class Tester {
 public:
  // testing for default constructor is done for you
  void testDefCtor() {
    IntList il;
    assert(il.head == NULL);
    assert(il.tail == NULL);
    assert(il.getSize() == 0);
  }
  // example of another method you might want to write
  void testAddFront() {
    // WRITE ME
    IntList il;

    il.addFront(50);
    assert(il.head->data == 50);
    assert(il.tail->data == 50);
    assert(il.head->prev == NULL);
    assert(il.head->next == NULL);
    assert(il.tail->prev == NULL);
    assert(il.tail->next == NULL);
    assert(il.getSize() == 1);
    il.addFront(3);
    assert(il.head->data == 3);
    assert(il.head->next->data == 50);
    assert(il.tail->data == 50);
    assert(il.tail->prev->data == 3);
  }

  void testAddBack() {
    IntList il;
    il.addBack(3);
    assert(il.head->data == 3);
    assert(il.tail->data == 3);
    assert(il.head->prev == NULL);
    assert(il.head->next == NULL);
    assert(il.tail->prev == NULL);
    assert(il.tail->next == NULL);
    assert(il.getSize() == 1);
    il.addBack(50);
    assert(il.head->data == 3);
    assert(il.head->next->data == 50);
    assert(il.tail->data == 50);
    assert(il.tail->prev->data == 3);
  }
  void testROT() {
    IntList il1;
    for (int i = 0; i < 5; i++) {
      il1.addBack(i);
    }
    IntList il2(il1);
    assert(il2.getSize() == 5);
    il2.addBack(5);
    assert(il2.getSize() == 6);
    IntList il3;
    il3 = il2;
    assert(il3.getSize() == 6);
    il1 = il3;
    assert(il1.getSize() == 6);
  }
  // many more tester methods

  void testRemove() {
    IntList il1;
    bool res;
    res = il1.remove(il1.head->data);
    assert(res == false);
    il1.addBack(50);
    res = il1.remove(il1.head->data);
    assert(res);
    assert(il1.head == NULL);
    assert(il1.tail == NULL);
    assert(il1.getSize() == 0);
    for (int i = 0; i < 3; i++) {
      il1.addBack(i);
    }
    res = il1.remove(il1[1]);
    assert(res);
    assert(il1.getSize() == 2);
    assert(il1.head->next->data == 2);
    assert(il1[1] == 2);
    assert(il1.tail->prev->data == 0);
    res = il1.remove(il1[1]);
    assert(res);
    assert(il1.tail->data == 0);
    assert(il1.tail->next == NULL);
    assert(il1.head->data == 0);
    il1.addBack(1);
    il1.remove(il1[0]);
    assert(il1.head->data == 1);
    assert(il1.head->next == NULL);
    assert(il1.tail->prev == NULL);
    res = il1.remove(il1[0]);
    assert(res);
    assert(il1.head == NULL);
    assert(il1.tail == NULL);
    assert(il1.getSize() == 0);
    for (int i = 0; i < 5; i++) {
      il1.addBack(i);
    }
    assert(il1.getSize() == 5);
    il1.remove(il1[0]);
    assert(il1[0] == 1);
    assert(il1[3] == 4);
    assert(il1.head->prev == NULL);
    il1.remove(il1[2]);
    assert(il1[2] == 4);
    assert(il1.head->data == 1);
    assert(il1.head->next->data == 2);
    assert(il1.head->next->next->data == 4);
    assert(il1.tail->data == 4);
    assert(il1.tail->prev->data == 2);
    assert(il1.tail->prev->prev->data == 1);
    assert(il1.tail->next == NULL);
    assert(il1.head->prev == NULL);
  }
};
int main(void) {
  Tester t;
  t.testDefCtor();
  t.testAddFront();
  t.testAddBack();
  t.testROT();
  t.testRemove();
  return EXIT_SUCCESS;
}
