#include <stdio.h>
#include <stdlib.h>
unsigned power(unsigned x, unsigned y);
void check_helper(unsigned x, unsigned y, unsigned ans) {
  if (power(x, y) != ans) {
    exit(EXIT_FAILURE);
  }
}
int main(void) {
  //printf("%d", power(-1, 3));
  check_helper(3, 0, 1);
  check_helper(0, 0, 1);
  check_helper(0, 3, 0);

  check_helper(2, 3, 8);
  check_helper(-1, 2, 1);
  check_helper(-1, 3, -1);
  check_helper('a', 1, 97);
  //check_helper(' ', 'a', 0);
  //check_helper('a', 'b', 1993115841);

  //check_helper(1, 'a', 1);

  //check_helper(4, 1, 4);
  //check_helper(2, 2, 4);

  //check_helper(2, -3, 0);
  //check_helper(10, -4, 0);

  return EXIT_SUCCESS;
}
