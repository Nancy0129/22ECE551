#include "function.h"

int binarySearchForZero(Function<int, int> * f, int low, int high) {
  if (low >= high) {
    return low;
  }
  //if (f->invoke(low) >= 0) {
  //return low;
  // }
  //if (f->invoke(high - 1) <= 0) {
  //return high - 1;
  // }
  int half = (low + high) / 2;
  if (half == low) {
    return low;
  }
  if (f->invoke(half) > 0) {
    return binarySearchForZero(f, low, half);
  }
  else {
    return binarySearchForZero(f, half, high);
  }
  //else if (f->invoke(half) > 0) {
  //return binarySearchForZero(f, low, half);
  // }
}
