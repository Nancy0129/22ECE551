#include "circle.hpp"

#include <cmath>
Circle::Circle(Point p, double r) {
  center = p;
  radius = r;
}
void Circle::move(double dx, double dy) {
  center.move(dx, dy);
}

double Circle::intersectionArea(const Circle & otherCircle) {
  double d = center.distanceFrom(otherCircle.center);
  double r1 = radius;
  double r2 = otherCircle.radius;
  if (d > (r1 + r2)) {
    return 0;
  }
  if (d * d <= (r1 - r2) * (r1 - r2)) {
    double A1 = r1 * r1 * M_PI;
    double A2 = r2 * r2 * M_PI;
    if (A1 > A2) {
      return A2;
    }
    else {
      return A1;
    }
  }
  double d1 = (r1 * r1 - r2 * r2 + d * d) / (2 * d);
  double d2 = d - d1;
  double A1 = r1 * r1 * acos(d1 / r1) - d1 * sqrt(r1 * r1 - d1 * d1);
  double A2 = r2 * r2 * acos(d2 / r2) - d2 * sqrt(r2 * r2 - d2 * d2);
  return A1 + A2;
}
