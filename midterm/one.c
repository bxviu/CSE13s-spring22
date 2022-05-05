#include "midterm.h"

#include <stdio.h>

int num_with_highest_square(int a, int b, int c) {
  return (a*a > b*b) ? ((a*a > c*c) ? a : c) : ((b*b > c*c) ? b : c);
}
