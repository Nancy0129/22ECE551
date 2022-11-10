#include <iostream>
#include <stdexcept>

#include "bstmap.h"
#include "map.h"

int main(void) {
  BstMap<int, int> a;
  a.add(1, 1);
  a.add(2, 2);
  a.add(3, 3);
  int b = a.lookup(1);
  std::cout << "b is " << b << "\n";
  return 0;
}
