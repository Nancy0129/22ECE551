#include "readFreq.h"

#include <stdio.h>

#include <cstdlib>
#include <fstream>

void printSym(std::ostream & s, unsigned sym) {
  if (sym > 256) {
    s << "INV";
  }
  else if (sym == 256) {
    s << "EOF";
  }
  else if (isprint(sym)) {
    char c = sym;
    s << "'" << c << "'";
  }
  else {
    std::streamsize w = s.width(3);
    s << std::hex << sym << std::dec;
    s.width(w);
  }
}
uint64_t * readFrequencies(const char * fname) {
  //WRITE ME!
  std::ifstream f(fname);
  if (!f.is_open()) {
    std::cerr << "cannot open the file!\n";
    exit(EXIT_FAILURE);
  }
  uint64_t * res = new uint64_t[257]();
  int c;
  while ((c = f.get()) != -1) {
    res[c] += 1;
  }
  res[256] = 1;
  return res;
}
