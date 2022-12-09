#include "story.h"
int main(int argc, char ** argv) {
  if (argc != 2) {
    std::cerr << "Invalid number of argument!\n";
    return EXIT_FAILURE;
  }
  try {  // generate and play the story
    Story mystory(argv[1]);
    mystory.play();
  }  // catch and display the error
  catch (std::exception & ex) {
    std::cerr << ex.what() << "\n";
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
