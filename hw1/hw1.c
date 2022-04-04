#include "hw1.h"

#include <math.h>
#include <stdbool.h>
#include <stdio.h>

// For the value of Pi, please use M_PI, which is defined in math.h.
double area_of_disk(double radius) {
  // your code here
  double area = M_PI*radius*radius; 
  // remove all these UNUSED things when you actually write the function.
  UNUSED(radius);
  return area;
}

double area_of_ring(double outer_radius, double inner_radius) {
  // your code here
  double area = area_of_disk(outer_radius) - area_of_disk(inner_radius);
  UNUSED(outer_radius);
  UNUSED(inner_radius);
  return area;
}

int bigger_minus_smaller(int a, int b) {
  // your code here
  int result = 0;
  if (a > b) {
    result = a - b;
  }
  else {
    result = b - a;
  }
  UNUSED(a);
  UNUSED(b);
  return result;
}

bool value_in_range(int lower_bound, int x, int upper_bound) {
  // your code here
  bool result = false;
  if (lower_bound <= x && x <= upper_bound) {
    result = true;
  }
  UNUSED(lower_bound);
  UNUSED(upper_bound);
  UNUSED(x);
  return result;
}
