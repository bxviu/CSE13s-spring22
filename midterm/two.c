#include "midterm.h"

#include <stdio.h>
#include <math.h>

double *exponents(int start, int end, double power) {
  double *array;
  //if the start and end are the same, create array of length 1, otherwise create it on the amount of numbers between start and end.
  if (start == end) { array = calloc(1, sizeof(double)); }
  else { array = calloc((end-start+1), sizeof(double)); }
  for (int i = 0; i <= (end-start); i++){
    //set element at index i to the starting number plus i, raised to the inputted power.
    array[i] = pow(i+start, power);
  }
  return array;
}
