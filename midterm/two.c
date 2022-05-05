#include "midterm.h"

#include <stdio.h>
#include <math.h>

double *exponents(int start, int end, double power) {
  double *array;
  if (start == end) { array = malloc(sizeof(double)*(end-start)); }
  else { array = malloc(sizeof(double)); }
  for (int i = 0; i <= end-start; i++){
    array[i] = pow(i+start, power);
  }
  return array;
}
