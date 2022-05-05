#include "midterm.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void swap(char *a, char *b) {
  char tmp = *a;
  *a = *b;
  *b = tmp;
}

char *alphabetize_word(char *word) {
  char *alphabetized = strdup(word);
  int smallest;
  int smallest_index;

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

  return alphabetized;
}
