#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "rand_story.h"
int main(int argc, char ** argv) {
  int del = 0;
  if (argc == 4) {
    if (strcmp(argv[1], "-n") != 0) {
      fprintf(stderr, "Undefined option: %s\n", argv[1]);
      return EXIT_FAILURE;
    }
    del = 1;
  }
  else {
    checkArgc(argc, 3);
  }
  catarray_t * cats = generateCat(argv[1 + del]);
  if (cats == NULL) {
    return EXIT_FAILURE;
  }
  FILE * story = fopen(argv[2 + del], "r");
  if (story == NULL) {
    perror("Cannot open the story file!");
    freeCat(cats);
    return EXIT_FAILURE;
  }
  updateStory(story, cats, del);
  return EXIT_SUCCESS;
}
