#include "midterm.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void swap(char *a, char *b) {
  char temp = *a;
  *a = *b;
  *b = temp;
}

char *alphabetize_word(char *word) {
  //create a pointer to a duplicate of inputted word
  char *alphabetized = strdup(word);
  int smallest;
  int smallest_index;

  /*iterate through the string, moving the lower values, which is the order of lower case letters of alphabet in ascii, 
  to the front of the string, and then doing it again until the end is reached.*/
  for (int i = 0; alphabetized[i] != '\0'; i++) {
    smallest = alphabetized[i];
    smallest_index = i;

    for (int j = i; alphabetized[j] != '\0'; j++) {
      if (alphabetized[j] < smallest) {
        smallest = alphabetized[j];
        smallest_index = j;
      }
    }
    swap((alphabetized + i), (alphabetized + smallest_index));
  }
  int* b;
  int c = 4;
  b = &c;
  printf("%X",(int)b);
  return alphabetized;
}
