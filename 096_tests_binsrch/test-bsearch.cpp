#include <assert.h>

#include <cmath>
#include <cstdlib>
#include <iostream>

#include "function.h"

class SinFunction : public Function<int, int> {
 public:
  virtual int invoke(int arg) { return arg - 10; }
};

class SinFunction2 : public Function<int, int> {
 public:
  virtual int invoke(int arg) { return arg - 100; }
};

int binarySearchForZero(Function<int, int> * f, int low, int high);

class CountedIntFn : public Function<int, int> {
 protected:
  unsigned remaining;
  Function<int, int> * f;
  const char * mesg;

 public:
  CountedIntFn(unsigned n, Function<int, int> * fn, const char * m) :
      remaining(n), f(fn), mesg(m) {}
  virtual int invoke(int arg) {
    if (remaining == 0) {
      fprintf(stderr, "Too many function invocations in %s\n", mesg);
      exit(EXIT_FAILURE);
    }
    remaining--;
    return f->invoke(arg);
  }
};

void check(Function<int, int> * f,
           int low,
           int high,
           int expected_ans,
           const char * mesg) {
  unsigned n;
  if (low < high) {
    n = log2(high - low) + 1;
    //n = 5;
  }
  else {
    n = 1;
  }
  CountedIntFn countFun(n, f, mesg);

  int ans = binarySearchForZero(&countFun, low, high);
  //  std::cout << ans << "\n";
  assert(ans == expected_ans);
}

int main(void) {
  SinFunction f1;
  SinFunction2 f2;
  check(&f1, 0, 1280, 10, "f1 normal");
  check(&f1, 0, 100, 10, "cannot divide");
  check(&f1, 100, 10, 100, "f1 low>high");
  check(&f1, 0, 4, 3, "f1 less than 10");
  check(&f1, 20, 500, 20, "f1 more than 10");
  check(&f1, 10, 10, 10, "f1 is 10");
  check(&f2, 0, 100, 99, "f1 round");

  return EXIT_SUCCESS;
}
