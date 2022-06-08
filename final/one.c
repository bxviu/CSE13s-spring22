#include "final.h"

#include <stdio.h>

size_t word_count(char *text) {
  // Your code here!
  // Count up all the words that occur in the given string. A new word starts
  // when you see a letter a-z or A-Z.
  size_t count = 0;
  int sameWord = 0;
  for (int i = 0; text[i] != '\0'; i++){
    if (!sameWord && ((text[i] >= 'a' && text[i] <= 'z') || (text[i] >= 'A' && text[i] <= 'Z'))){
      sameWord = 1;
      count++;
    } 
    else if (sameWord && (text[i] < 'A' || (text[i] > 'Z' && text[i] < 'a') || text[i] > 'z')){
      sameWord = 0;
    }
  }
  return count;
}
