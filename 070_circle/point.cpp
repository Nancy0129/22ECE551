#include "point.hpp"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#include <cmath>
#include <cstdio>
void Point::move(double dx, double dy) {
  x += dx;
  y += dy;
}
double Point::distanceFrom(const Point & p) {
  double dx, dy;
  dx = x - p.x;
  dy = y - p.y;
  return sqrt(dx * dx + dy * dy);
}
