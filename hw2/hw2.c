/*
 * All of your code goes in here. You need to finish these functions.
 */

#include "hw2.h"

int next_collatz_number(int n) {
  if (n % 2 == 0){
    return n/2;
  }
  return ((n*3)+1);
}

int count_collatz_steps(int n) {
  int count = 0;
  while (n != 1){
    n = next_collatz_number(n);
    count++;
  }
  return count;
}

int maximum(int *nums, int len) {
  int max = nums[0];
  for (int i = 0; i < len; i++){
    if (nums[i] > max){
      max = nums[i];
    }
  }
  return max;
}

int sum_positive(int *nums, int len) { 
  int sum = 0;
  for (int i = 0; i < len; i++){
    if (nums[i] > 0){
      sum += nums[i];
    }
  }
  return sum;
}

int count_negative(int *nums, int len) {
  int count = 0;
  for (int i = 0; i < len; i++){
    if (nums[i] < 0){
      count++;
    }
  }
  return count;
}
