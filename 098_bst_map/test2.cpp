#include <iostream>
#include <stdexcept>

#include "bstmap.h"
#include "map.h"

int main(void) {
  BstMap<int, int> a;
  //  int b = a.lookup(9);
  a.print_tree();
  a.add(9, 9);
  a.add(7, 7);
  a.add(81, 81);
  a.add(4, 4);
  a.add(1, 1);
  a.add(6, 6);
  a.add(32, 32);
  a.add(64, 64);
  a.add(99, 99);
  a.add(16, 16);
  a.add(22, 22);
  a.add(81, 888);
  a.add(20, 20);
  a.add(30, 35);
  a.print_tree();

  a.remove(9);
  a.remove(9);
  a.add(9, 6);
  a.add(9, 7);
  a.remove(9);
  a.print_tree();
  a.remove(16);
  a.print_tree();
  a.remove(20);
  a.print_tree();
  a.remove(22);
  a.print_tree();
  a.remove(30);
  a.print_tree();
  a.remove(32);
  a.print_tree();
  a.remove(64);
  a.print_tree();
  a.remove(81);
  a.print_tree();
  a.remove(99);
  a.print_tree();
  a.remove(7);
  a.print_tree();
  a.remove(4);
  a.print_tree();
  a.remove(6);
  a.print_tree();
  a.remove(1);
  a.print_tree();
  a.add(9, 9);
  a.add(16, 16);
  const int & b = a.lookup(16);
  a.remove(9);
  a.print_tree();
  std::cout << "b is " << b << "\n";
  // b = a.lookup(12);
  //std::cout << "b is " << b << "\n";
  return 0;
}
