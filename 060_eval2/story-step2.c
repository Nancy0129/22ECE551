#include "rand_story.h"

int main(int argc, char ** argv) {
  checkArgc(argc, 2);
  catarray_t * cats = generateCat(argv[1]);
  if (cats == NULL) {
    return EXIT_FAILURE;
  }
  printWords(cats);
  freeCat(cats);
  return EXIT_SUCCESS;
}
