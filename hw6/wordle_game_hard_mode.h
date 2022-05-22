#pragma once

#include <stdbool.h>
#include <stdio.h>

typedef struct {
  char tried[26];
  char partial[8];
  char correct[8];
} Guesses;

bool score_guess(char *secret, char *guess, char *result, Guesses* g);

bool valid_guess(char *guess, char **vocabulary, size_t num_words, Guesses* g, char* secret);

char **load_vocabulary(char *filename, size_t *num_words);

void free_vocabulary(char **vocabulary, size_t num_words);

// Idea for the UNUSED macro from Stack Overflow user mtvec. Thanks!
// https://stackoverflow.com/a/3599170
#define UNUSED(x) (void)(x)
