#include <cstdio>
#include <sstream>
#include <string>
using namespace std;
class Expression {
 public:
  Expression() {}
  virtual string toString() const = 0;
  virtual long evaluate() const = 0;
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
  long evaluate() const { return n; }
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
  long evaluate() const { return left->evaluate() + right->evaluate(); }
  ~PlusExpression() {
    delete left;
    delete right;
  }
};

class MinusExpression : public Expression {
  Expression * left;
  Expression * right;

 public:
  MinusExpression(Expression * lhs, Expression * rhs) : left(lhs), right(rhs) {}
  string toString() const {
    stringstream expr;
    expr << "(";
    expr << left->toString();
    expr << " - ";
    expr << right->toString();
    expr << ")";
    return expr.str();
  }
  long evaluate() const { return left->evaluate() - right->evaluate(); }

  ~MinusExpression() {
    delete left;
    delete right;
  }
};

class TimesExpression : public Expression {
  Expression * left;
  Expression * right;

 public:
  TimesExpression(Expression * lhs, Expression * rhs) : left(lhs), right(rhs) {}
  string toString() const {
    stringstream expr;
    expr << "(";
    expr << left->toString();
    expr << " * ";
    expr << right->toString();
    expr << ")";
    return expr.str();
  }
  long evaluate() const { return left->evaluate() * right->evaluate(); }

  ~TimesExpression() {
    delete left;
    delete right;
  }
};
class DivExpression : public Expression {
  Expression * left;
  Expression * right;

 public:
  DivExpression(Expression * lhs, Expression * rhs) : left(lhs), right(rhs) {}
  string toString() const {
    stringstream expr;
    expr << "(";
    expr << left->toString();
    expr << " / ";
    expr << right->toString();
    expr << ")";
    return expr.str();
  }
  long evaluate() const { return left->evaluate() / right->evaluate(); }

  ~DivExpression() {
    delete left;
    delete right;
  }
};
