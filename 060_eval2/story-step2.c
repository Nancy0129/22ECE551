#include "rand_story.h"

int main(int argc, char ** argv) {
  checkArgc(argc, 2);
  FILE * f = OpenCheckFile(argv[1]);
  catarray_t * cats = generateCat(f);
  if (cats == NULL) {
    return EXIT_FAILURE;
  }
  printWords(cats);
  freeCat(cats);
  if (fclose(f) != 0) {
    perror("Failed to close the input file!\n");
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
