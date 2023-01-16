#include <cstdlib>
#include <iostream>
#include <vector>
class CurrencyData {
 protected:
  double dollar_ex_rate;

 public:
  explicit CurrencyData(double ex_rate) : dollar_ex_rate(ex_rate) {
    std::cout << "CurrencyData(" << ex_rate << ")\n";
  }
  virtual ~CurrencyData() { std::cout << "~CurrencyData()\n"; };
  virtual void printDollarAmt(double money) = 0;
};
class Euro : public CurrencyData {
 public:
  Euro() : CurrencyData(1.1) { std::cout << "Euro()\n"; }
  virtual ~Euro() { std::cout << "~Euro()\n"; };
  virtual void printDollarAmt(double money) {
    std::cout << money << " Euro = " << money * dollar_ex_rate << " Dollars\n";
  }
};
class Yuan : public CurrencyData {
 public:
  Yuan() : CurrencyData(0.15) { std::cout << "Yuan()\n"; }
  virtual ~Yuan() { std::cout << "~Yuan()\n"; };
  virtual void printDollarAmt(double money) {
    std::cout << money << " Yuan = " << money * dollar_ex_rate << " Dollars\n";
  }
};
int main(void) {
  std::vector<CurrencyData *> vec;
  vec.push_back(new Euro());
  vec.push_back(new Yuan());
  double amt = 10;
  for (std::vector<CurrencyData *>::iterator it = vec.begin(); it != vec.end(); ++it) {
    (*it)->printDollarAmt(amt);
    amt *= 10;
    delete *it;
  }
  return EXIT_SUCCESS;
}
