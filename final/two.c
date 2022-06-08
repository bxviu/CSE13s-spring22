#include "final.h"

#include <stdio.h>

char **alphabet_sequences(int maxsize) {
  // Your code here!
  // remember, you're going to need to allocate the array of strings you're
  // returning. and you'll also need to allocate each string in that array.
  char** alphabet_array = (char**)calloc(maxsize, sizeof(char*));
  for (int i = 0; i < maxsize; i++){
    alphabet_array[i] = (char*)calloc(i+2, sizeof(char));
    for (int j = 0; j <= i; j++){
      alphabet_array[i][j] = j + 'a' - (26*((int)j/26));
    }
    alphabet_array[i][i+1] = '\0';
  }
  return alphabet_array;
}
