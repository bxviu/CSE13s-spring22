#include "midterm.h"

#include <stdio.h>

LLint *push(LLint *list, int val) {
  LLint *out = (LLint *)calloc(1, sizeof(LLint));
  out->next = list;
  out->val = val;
  return out;
}

int reduce(LLint *nums, int (*f)(int, int), int initial) {
  //recursively calls reduce to keep going to the next node in the linked list and calling the inputted function on it's value, stopping when there is no more node
  return (nums != NULL) ? (*f)(reduce(nums->next, f, initial), nums->val) : initial;
}
