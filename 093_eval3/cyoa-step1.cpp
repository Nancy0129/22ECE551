#include "story.h"

int main(int argc, char ** argv) {
  if (argc != 2) {
    std::cerr << "Invalid number of argument!\n";
    return EXIT_FAILURE;
  }
  try {
    Story mystory(argv[1]);
    std::cout << mystory;
  }
  catch (std::invalid_argument & ex) {
    std::cerr << "Cannot generate/print story: " << ex.what() << "\n";
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
