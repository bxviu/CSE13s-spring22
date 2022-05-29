#include "review.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Functions for you to implement. Most of the work for this homework will be
// done in here, but you'll also need to make changes to review.h and yelling.c.

// Problem 1
void sum_and_difference(int a, int b, int *sum, int *difference) {
  //  TODO(you): your code here
  *sum = a + b;
  *difference = a - b;
}

// Problem 2

// This one ought to be recursive.
size_t ll_length(LLint *node) {
  //  TODO(you): your code here
  if (node == NULL){
    return 0;
  }
  return 1 + ll_length(node->next);
}

// Do this one iteratively.
size_t ll_length_iterative(LLint *node) {
  //  TODO(you): your code here
  size_t len = 0;
  LLint *temp = node;
  while (temp != NULL){ 
    temp = temp->next;
    len++;
  }
  return len;
}

// Problem 3.

void reverse_doubles_with_stack(double *array, size_t array_len) {
  // This function will reverse the order of the array pointed to by *array.
  // Make sure to define your linked list data structure in review.h, and use
  // stack behavior (LIFO) to get the numbers in the reversed order.
  // There is a way to do this without a stack data structure, I know. But this
  // is for practice with data structures.
  //
  //  TODO(you): your code here
  LLdouble* top;
  top = (LLdouble*)calloc(1,sizeof(LLdouble));
  for (size_t i = 0; i < array_len; i++) {
    LLdouble *newLLdouble = (LLdouble*)malloc(sizeof(LLdouble));
    newLLdouble->next = top;
    newLLdouble->val = array[i];
    top = newLLdouble;
  }
  for (size_t i = 0; i < array_len; i++) {
    array[i] = top->val;
    LLdouble* deleteThis = top;
    top = top->next;
    free(deleteThis);
  }
  free(top);
}

// Problem 4.

tnode *word_observe(char *word, tnode *node) {
  // This function returns a pointer to a tnode because you may have to allocate
  // a new one. You might take a NULL pointer to start with.
  // Also, this means that you can very cleanly do this with recursion.
  if (node == NULL) {
    node = (tnode*)calloc(1,sizeof(tnode));
    node->word = strdup(word);
    node->count++;
    node->left = node->right = NULL;
  }
  else if (!strcmp(node->word,word)){
    node->count++;
  }
  else if (strcmp(node->word,word) < 0){
    node->left = word_observe(word, node->left);
  }
  else {
    node->right = word_observe(word, node->right);
  }
  return node;
}

int word_count(char *word, tnode *node) {
  // Default return values; here for you to change.
  if (node == NULL) {
    return 0;
  }
  if (!strcmp(node->word,word)){
    return node->count;
  }
  return word_count(word, node->left) + word_count(word, node->right);
}

void delete_tree(tnode *node) {
  // Free the whole tree and all associated memory. This can be recursive or
  // not, your choice!
  if (node == NULL) { return; }
  delete_tree(node->left);
  delete_tree(node->right);
  free(node->word);
  free(node);
}
