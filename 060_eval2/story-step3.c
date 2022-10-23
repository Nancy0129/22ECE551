#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "rand_story.h"

int main(int argc, char ** argv) {
  checkArgc(argc, 3);
  catarray_t * cats = generateCat(argv[1]);
  if (cats == NULL) {
    return EXIT_FAILURE;
  }
  FILE * story = fopen(argv[2], "r");
  if (story == NULL) {
    perror("Cannot open the story file!");
    freeCat(cats);
    return EXIT_FAILURE;
  }
  updateStory(story, cats, 0);
  return EXIT_SUCCESS;
}
