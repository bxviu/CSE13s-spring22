/*
 * All of your code goes in here. You need to finish these functions.
 */

#include "hw3.h"
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <limits.h>

bool str_suffix(char *haystack, char *needle) {
  if (*needle == '\0'){
    return true;
  }
  for (int i = 0; haystack[i] != '\0'; i++){
    if (haystack[i] == needle[0]){
      for (int j = 0; needle[j] != '\0'; j++){
        if (haystack[i+j] != needle[j]){
	  break;
	}
	else if (haystack[i+j+1] == '\0' && needle[j+1] == '\0'){
	  return true;
	}
      }
    }
  }
  return false;
}

float dot_product(float *vec_a, float *vec_b, int length) {
  float sum = 0;
  for (int i = 0; i < length; i++) {
    sum += vec_a[i] * vec_b[i];
  }
  return sum;
}

int reduce(int *nums, int length, int (*f)(int,int), int initial) {
  int result = initial;
  for (int i = 0; i < length; i++){
    result = (*f)(result,nums[i]);
  }
  return result;
}


// These two functions will end up as a *single call to reduce*, but you'll have
// to write a new helper function for each of them. Those helper functions will
// be quite short though!

int compare_greater(int a, int b){
  return (a > b) ? a : b;
}

int maximum_with_reduce(int *nums, int length) {
  return reduce(nums, length, &compare_greater, INT_MIN);
}

int add_positive(int a, int b){
  return (b > 0) ? a+b : a;
}

int sum_positive_with_reduce(int *nums, int length) {
  return reduce(nums, length, &add_positive, 0);
}
