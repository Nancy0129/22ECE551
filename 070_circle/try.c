#include <stdio.h>
#include <stdlib.h>

int main(void) {
  int n = 4;
  double * x = malloc(sizeof(n));
  x[0] = 0;
  free(x);
  return EXIT_SUCCESS;
}
