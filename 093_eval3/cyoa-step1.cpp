#include "story.h"

int main(int argc, char ** argv) {
  if (argc != 2) {
    std::cerr << "Invalid number of argument!\n";
    return EXIT_FAILURE;
  }
  try {  // print story
    Story mystory(argv[1]);
    std::cout << mystory;
  }
  catch (std::exception & ex) {  // show the error
    std::cerr << ex.what() << "\n";
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
