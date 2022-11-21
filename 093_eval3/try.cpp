#include <cstdlib>
#include <exception>
#include <fstream>
#include <iostream>
#include <string>
/*
class SotryExeption : public std::exception {
 private:
  std::string message;

 public:
  SotryExeption(const char * m) : message("Invalid Input in story.txt: ") {
    message += m;
  }
  ~SotryExeption() {}
  std::string & printErr() { return message; }
};
int main(void) {
  try {
    throw SotryExeption("The number is not pos");
  }
  catch (SotryExeption & e) {
    std::cerr << e.printErr() << "\n";
  }
  return 0;
}
*/

int main(int argc, char ** argv) {
  /* if (argc == 2) {
    std::string dir = argv[1];
    std::string file_name = dir + "story.txt";
    std::ifstream f(file_name.c_str());
    std::string line;
    std::string user_in;
    char * endptr;
    while (std::getline(f, line)) {
      //  std::cin >> user_in;
      size_t find = line.find("@");
      if (line.empty()) {
        std::cout << "empty line: \n";
      }
      std::cout << line << "\n";
      if (find != std::string::npos) {
        std::cout << line.substr(0, find) << "\n";
        std::cin >> user_in;
        size_t o = std::strtoul(user_in.c_str(), &endptr, 10);
        if (endptr[0] == '\0') {
          std::cout << o << "\n";
        }
        //std::cout << endptr << "\n";
        else {
          std::cout << "Please Enter again! \n";
          std::cin >> user_in;
        }

        //std::cout << user_in << "\n";
      }
    }*/
  std::string user_in;
  char * endptr;
  while (std::getline(std::cin, user_in)) {
    if (user_in.find_first_not_of(" \t\n\v\f\r") != std::string::npos) {
      size_t o = std::strtoul(user_in.c_str(), &endptr, 10);

      if (endptr[0] == '\0') {
        std::cout << o << "\n";
      }
      else {
        std::cout << "That is not a valid choice, please try again\n";
      }
    }
  }
  return 0;
}
