#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#include "pandemic.h"
int main(void) {
  char word[] = "xyz,184 4 6 744";
  int i = 0;
  while (word[i] != ',') {
    i++;
  }
  char * nums = word + i + 1;
  char * pr;
  uint64_t a = strtoull(nums, &pr, 10);
  double b = (double)a / 100000;

  if (*pr != '\0') {
    printf("%d\n", 1);
  }
  printf("%lu\n", a);
  printf("%s\n", pr);
  printf("%s\n", nums);
  printf("%lf\n", b);
  return 0;
}
