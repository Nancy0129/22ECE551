#include <stdio.h>
#include <stdlib.h>

size_t maxSeq(int * array, size_t n) {
  if (n <= 1) {
    return n;
  }
  int l = 1;
  int maxl = 0;
  int ip = array[0];
  for (int i = 1; i < n; i++) {
    if (array[i] > ip) {
      l++;
    }
    else {
      if (l > maxl) {
        maxl = l;
      }
      l = 1;
    }
    ip = array[i];
  }
  if (l > maxl) {
    maxl = l;
  }
  return maxl;
}

//void check_result(int * array, size_t n, size_t res) {
//if (maxSeq(array, n) != res) {
//  exit(EXIT_FAILURE);
//}
//}

//int main(void) {
//  int myArray0[] = {1, 2, 3, 4, 5};
//
//  int myArray1[] = {1, 1, 1, 1, 1};
//
//  int myArray2[] = {3, 2, 1};
//
//  int myArray3[] = {1, 1, 1, 1, 2};
//
//  int myArray4[] = {1};

//int myArray5[] = {-1, -2, -3, -4, 5};
//printf("%ld   %d\n", maxSeq(myArray0, 5), 5);
//printf("%ld   %d\n", maxSeq(myArray1, 5), 1);
//printf("%ld   %d\n", maxSeq(myArray2, 3), 1);
//printf("%ld   %d\n", maxSeq(myArray3, 5), 2);
//printf("%ld   %d\n", maxSeq(myArray4, 1), 1);
//printf("%ld   %d\n", maxSeq(myArray5, 5), 2);
//check_result(NULL, 0, 0);
//check_result(myArray0, 5, 5);
//check_result(myArray1, 5, 1);
//check_result(myArray2, 3, 1);
//check_result(myArray3, 5, 2);
//check_result(myArray4, 1, 1);
//check_result(myArray5, 5, 2);
//return EXIT_SUCCESS;
//}
