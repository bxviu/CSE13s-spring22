#include "midterm.h"

#include <stdio.h>

int num_with_highest_square(int a, int b, int c) {
  /*This checks if a^2 is greater than b^2, if it is true, then it checks if a^2 is greater than c^2, if it is true, then it returns a.
  However, if it is false, then it returns c, since that means that a^2 is between c^2 and b^2, in which b^2 is already known to be less than a^2.
  If the first check is false and a^2 is less than b^2, then the function checks if b^2 is greater than c^2. The same logic applies here as written
  in the previous sentences, except a^2 is replaced with b^2.*/
  return (a*a > b*b) ? ((a*a > c*c) ? a : c) : ((b*b > c*c) ? b : c);
}
