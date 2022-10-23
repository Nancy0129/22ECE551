#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
  char a[] = "12\n";
  int b = atoi(a);
  printf("%d\n", b);
  return EXIT_SUCCESS;
}
