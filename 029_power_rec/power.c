#include <stdio.h>
#include <stdlib.h>

unsigned power(unsigned x, unsigned y) {
  if (y == 0) {
    return 1;
  }
  else if (x == 1) {
    return 1;
  }
  else if (y < 0) {
    return 0;
  }
  else if (x == 0) {
    return 0;
  }
  else if (y == 1) {
    return x;
  }
  else {
    return x * power(x, y - 1);
  }
}

//void check_helper(unsigned x, unsigned y, unsigned ans) {
//if (power(x, y) != ans) {
//exit(EXIT_FAILURE);
//}
//printf("Out:%d, expected:%d \n", power(x, y), ans);
//}

//int main(void) {
//check_helper(3, 0, 1);
//check_helper(0, 0, 1);
//check_helper(0, 3, 0);

//check_helper(2, 3, 8);
//check_helper(-1, 2, 1);
//check_helper(-1, 3, -1);
//check_helper('a', 1, 97);
//return EXIT_SUCCESS;
//}
