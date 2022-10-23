#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "rand_story.h"

int main(int argc, char ** argv) {
  checkArgc(argc, 2);                 // check the argument number
  FILE * f = OpenCheckFile(argv[1]);  // open and check if the file is NULL
  char * line = NULL;
  size_t size = 0;
  while (getline(&line, &size, f) != -1) {  // process line by line
    blankarr_t * blanks = checkStory(line);
    size_t pre = strlen(line);
    if (blanks == NULL) {  // if a line has format error -> exit faliure
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
  checkCloseFile(f);
  return EXIT_SUCCESS;
}
