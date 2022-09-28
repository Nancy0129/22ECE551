#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

int readMax(FILE * f, char array[10][10]) {
  char c;
  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 10; j++) {
      if ((c = fgetc(f)) == EOF) {
        fprintf(stderr, "Too short text!\n");
        return EXIT_FAILURE;
      }
      if (c == '\n') {
        fprintf(stderr, "Too short row\n");
        return EXIT_FAILURE;
      }
      array[j][9 - i] = c;
    }
    if ((c = fgetc(f)) != '\n') {
      fprintf(stderr, "Too long row\n");
      return EXIT_FAILURE;
    }
  }
  if ((c = fgetc(f)) != EOF) {
    fprintf(stderr, "Too long texts!\n");
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}

int main(int argc, char ** argv) {
  if (argc != 2) {
    fprintf(stderr, "Usage: encrypt key inputFileName\n");
    return EXIT_FAILURE;
  }
  FILE * f = fopen(argv[1], "r");
  if (f == NULL) {
    perror("Could not open file!\n");
    return EXIT_FAILURE;
  }
  char array[10][10];
  int out = readMax(f, array);
  if (out != EXIT_SUCCESS) {
    return EXIT_FAILURE;
  }
  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 10; j++) {
      printf("%c", array[i][j]);
    }
    printf("\n");
  }

  if (fclose(f) != 0) {
    perror("Failed to close the input file!\n");
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
