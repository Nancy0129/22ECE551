#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

int readMax(FILE * f, char array[10][10]) {
  char c;
  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 10; j++) {
      c = fgetc(f);
      if (c == EOF) {
        fprintf(stderr, "Too short text!");
        return EXIT_FAILURE;
      }
      if (c == '\n') {
        fprintf(stderr, "Too short row");
        return EXIT_FAILURE;
      }
      array[j][9 - i] = c;
    }
    if ((c = fgetc(f)) != '\n') {
      fprintf(stderr, "Too long row");
      return EXIT_FAILURE;
    }
  }
  if ((c = fgetc(f)) != EOF) {
    fprintf(stderr, "Too long texts!");
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
    perror("Could not open file");
    return EXIT_FAILURE;
  }
  char array[10][10];
  readMax(f, array);
  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 10; j++) {
      printf("%c", array[i][j]);
    }
    printf("\n");
  }

  if (fclose(f) != 0) {
    perror("Failed to close the input file!");
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
