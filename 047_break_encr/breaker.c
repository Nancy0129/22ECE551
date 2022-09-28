#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
void countC(FILE * f, int * save) {
  int c;
  while ((c = fgetc(f)) != EOF) {
    if (isalpha(c)) {
      c = tolower(c);
      save[c - 97]++;
    }
  }
  return;
}

int findMax(int * save) {
  int maxI = 0;
  int maxC = 0;
  for (int i = 0; i < 26; i++) {
    if (save[i] > maxC) {
      maxI = i;
      maxC = save[i];
    }
  }
  if (maxC == 0) {
    fprintf(stderr, "Invalid Input file- not letter!");
    return EXIT_FAILURE;
  }
  if (maxI < 4) {
    maxI += 26;
  }
  return maxI;
}

int main(int argc, char ** argv) {
  if (argc != 2) {
    fprintf(stderr, "Usage: encrypt key inputFileName\n");
    return EXIT_FAILURE;
  }

  FILE * f = fopen(argv[1], "r");
  if (f == NULL) {
    perror("Could not open file");
    return EXIT_FAILURE;
  }
  int array[26] = {0};
  countC(f, array);
  int res = findMax(array) + 97 - 101;
  if (res < 0 || res >= 26) {
    perror("Invalid Key value!");
    return EXIT_FAILURE;
  }
  printf("%d\n", res);
  if (fclose(f) != 0) {
    perror("Failed to close the input file!");
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
