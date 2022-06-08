#include "final.h"

#include <stdio.h>

int count_values_at_least(int value, BinaryTree *tree) {
  // Your code here!
  // Remember, this is just a regular binary tree, not a binary *search* tree.
  if (tree == NULL) {
    return 0;
  }
  return ((value <= tree->val) ? 1 : 0) + count_values_at_least(value, tree->left) + count_values_at_least(value, tree->right);
}
