#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>
using namespace std;

int main(void) {
  string a(5, 'a');
  cout << a << endl;
  string b("12345abcde");
  stringstream B("12345abcde");
  return EXIT_SUCCESS;
}
