#include <iostream>
#include <stdexcept>

#include "bstmap.h"
#include "map.h"

int main(void) {
  BstMap<int, int> a;
  //  int b = a.lookup(9);
  a.add(2, 2);

  a.add(1, 1);
  a.add(0, 0);
  //a.add(3, 3);
  a.add(4, 4);
  //a.add(0, 5);
  try {
    int b = a.lookup(9);
    std::cout << "b is " << b << "\n";
  }
  catch (std::invalid_argument const & ex) {
    std::cout << "#1: " << ex.what() << '\n';
  }
  //b = a.lookup(0);

  //a.remove(2);
  a.add(2, 77);

  //std::cout << "b is " << b << "\n";
  return 0;
}
