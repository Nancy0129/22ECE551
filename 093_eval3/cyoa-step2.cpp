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
  catch (std::invalid_argument & ex) {
    std::cerr << "Cannot generate story: " << ex.what() << "\n";
    return EXIT_FAILURE;
  }
  catch (std::range_error & ex) {
    std::cerr << "The story is invalid: " << ex.what() << "\n";
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
