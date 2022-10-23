#include "point.hpp"
class Circle {
 private:
  Point center;
  double radius;

 public:
  Circle(Point p, double r);
  void move(double dx, double dy);
  double intersectionArea(const Circle & otherCircle);
};
