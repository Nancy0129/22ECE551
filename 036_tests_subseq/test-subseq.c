#include <stdio.h>
#include <stdlib.h>
size_t maxSeq(int * array, size_t n);

void check_result(int * array, size_t n, size_t res) {
  if (maxSeq(array, n) != res) {
    exit(EXIT_FAILURE);
  }
}

int main(void) {
  int myArray0[] = {1, 2, 3, 4, 5};

  int myArray1[] = {1, 1, 1, 1, 1};

  int myArray2[] = {3, 2, 1};

  int myArray3[] = {1, 1, 1, 1, 2};

  int myArray4[] = {1};

  int myArray5[] = {-1, -2, -3, -4, 5};
  //printf("%ld", maxSeq(myArray5, 5));
  check_result(NULL, 0, 0);
  check_result(myArray0, 5, 5);
  check_result(myArray1, 5, 1);
  check_result(myArray2, 3, 1);
  check_result(myArray3, 5, 2);
  check_result(myArray4, 1, 1);
  check_result(myArray5, 5, 2);
  return EXIT_SUCCESS;
}
