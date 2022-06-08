#include "final.h"

#include <stdio.h>
//#include <string.h>

char **alphabet_sequences(int maxsize) {
  // Your code here!
  // remember, you're going to need to allocate the array of strings you're
  // returning. and you'll also need to allocate each string in that array.
  char** alphabet_array = (char**)calloc(maxsize, sizeof(char*));
  for (int i = 0; i < maxsize; i++){
    for (int j = 0; j <= i; j++){
      alphabet_array[i] = (char*)calloc(j+2, sizeof(char));
      for (int k = 0; k <= j; k++){
	//if (maxsize/) {
          alphabet_array[i][k] = k + 'a' - (26*((int)k/26));
	/*}
	else {
          alphabet_array[i][k] = k + 'a';
	}*/
      }
      alphabet_array[i][j+1] = '\0';
    }
    //printf("%s\n", alphabet_array[i]);
  }
  return alphabet_array;
}
