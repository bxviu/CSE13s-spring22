#include "midterm.h"

#include <stdio.h>

LLint *push(LLint *list, int val) {
  LLint *out = (LLint *)calloc(1, sizeof(LLint));
  out->next = list;
  out->val = val;
  return out;
}

int reduce(LLint *nums, int (*f)(int, int), int initial) {
  return (nums != NULL) ? (*f)(reduce(nums->next, f, initial), nums->val) : initial;
}
