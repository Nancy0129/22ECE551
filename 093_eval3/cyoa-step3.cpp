#include "story.h"
int main(int argc, char ** argv) {
  if (argc != 2) {
    std::cerr << "Invalid number of argument!\n";
    return EXIT_FAILURE;
  }
  try {  // generate and show the winning path
    Story mystory(argv[1]);
    mystory.showWinPath();
  }  // catch and display the error
  catch (std::exception & ex) {
    std::cerr << ex.what() << "\n";
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
