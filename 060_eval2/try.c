#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
  char a[8] = "-56";
  char * endtr;
  //char * b = strndup(a + 2, 0);
  long b = strtoul(a, &endtr, 10);
  printf("%lu\n", b);
  if (endtr[0] == '\0') {
    printf("%d\n", 1);
  }
  printf("%s", endtr);
  //free(b);
  return EXIT_SUCCESS;
}
