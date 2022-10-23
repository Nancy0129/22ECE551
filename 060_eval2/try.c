#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
  char a[7] = "abcdef";
  char * b = strndup(a + 2, 0);
  printf("%s\n", b);
  free(b);
  return EXIT_SUCCESS;
}
