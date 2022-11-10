#include <iostream>
#include <stdexcept>

#include "bstmap.h"
#include "map.h"

int main(void) {
  BstMap<int, int> a;
  //  int b = a.lookup(9);
  a.add(10, 10);
  a.add(15, 15);
  a.add(5, 5);
  a.add(12, 0);
  a.add(13, 13);

  a.remove(13);
  //try {
  //int b = a.lookup(2);
  //std::cout << "b is " << b << "\n";
  // }
  //catch (std::invalid_argument const & ex) {
  //std::cout << "#1: " << ex.what() << '\n';
  // }
  int b = a.lookup(10);

  //  a.add(2, 77);

  std::cout << "b is " << b << "\n";
  b = a.lookup(12);
  std::cout << "b is " << b << "\n";
  return 0;
}
