#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "rand_story.h"

int main(int argc, char ** argv) {
  if (argc != 2) {
    fprintf(stderr, "Invalid number of arguments!\n");
    return EXIT_FAILURE;
  }
  FILE * f = fopen(argv[1], "r");
  if (f == NULL) {
    fprintf(stderr, "Cannot open the file!\n");
    return EXIT_FAILURE;
  }
  char * line = NULL;
  size_t size = 0;
  while (getline(&line, &size, f) != -1) {  // process line by line
    blankarr_t * blanks = checkStory(line);
    size_t pre = strlen(line);
    if (blanks == NULL) {  // if a line has format error -> exit faliure
      fprintf(stderr, "Invalid format story format:\n %s ", line);
      free(line);
      fclose(f);
      return EXIT_FAILURE;
    }
    for (size_t i = 0; i < blanks->n; i++) {  // replace the blanks
      const char * word = chooseWord(blanks->arr[i].cat, NULL);
      line = replaceWord(line, blanks->arr[i], word);
      updateBlank(blanks, i + 1, strlen(line) - pre);
      pre = strlen(line);
    }
    printf("%s", line);  // print the output line
    free(line);
    freeblank(blanks);
    line = NULL;
  }
  free(line);
  if (fclose(f) != 0) {
    perror("Failed to close the input file!\n");
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
