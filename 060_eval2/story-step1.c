#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "rand_story.h"

int main(int argc, char ** argv) {
  checkArgc(argc, 2);                 // check the argument number
  FILE * f = OpenCheckFile(argv[1]);  // open and check if the file is NULL
  updateStory(f, NULL, 0);
  return EXIT_SUCCESS;
}
