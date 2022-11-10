#include <iostream>
#include <stdexcept>

#include "bstmap.h"
#include "map.h"

int main(void) {
  BstMap<int, int> a;

  a.add(2, 2);

  a.add(1, 1);
  a.add(0, 0);
  a.add(3, 3);
  a.add(4, 4);
  a.add(0, 5);
  int b = a.lookup(9);
  b = a.lookup(0);
  std::cout << "b is " << b << "\n";
  //a.remove(2);
  a.add(2, 77);

  std::cout << "b is " << b << "\n";
  return 0;
}
