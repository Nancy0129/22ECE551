#include <iostream>
#include <stdexcept>

int main(void) {
  int * a = new int(10);
  std::cout << *a << "\n";
  delete a;
}
