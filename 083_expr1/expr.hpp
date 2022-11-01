#include <cstdio>
#include <sstream>
#include <string>
using namespace std;
class Expression {
 public:
  Expression() {}
  virtual string toString() const = 0;
  virtual ~Expression() {}
};
class NumExpression : public Expression {
  long n;

 public:
  NumExpression(long num) : n(num) {}
  string toString() const {
    stringstream a;
    a << n;
    return a.str();
  }
  ~NumExpression() {}
};
class PlusExpression : public Expression {
  Expression * left;
  Expression * right;

 public:
  PlusExpression(Expression * lhs, Expression * rhs) : left(lhs), right(rhs) {}
  string toString() const {
    stringstream expr;
    expr << "(";
    expr << left->toString();
    expr << " + ";
    expr << right->toString();
    expr << ")";
    return expr.str();
  }
  ~PlusExpression() {
    delete left;
    delete right;
  }
};
