#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
  char str1[] = "baaac";
  char str2[] = "Aaaafagadhghgga";
  printf("%d\n", strcmp(str1, str2));
  printf("%d\n", strcasecmp(str1, str2));
  char str3[] = "12345";
  //strncpy(str3, str2, 5);
  printf("%s\n", str1);
  printf("%d\n", atoi(str3));
  return EXIT_SUCCESS;
}
