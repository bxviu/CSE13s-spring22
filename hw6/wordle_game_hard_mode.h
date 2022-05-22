#pragma once

#include <stdbool.h>
#include <stdio.h>

//to hold the player's guesses
typedef struct {
  //letters that are not in the word
  char tried[30];
  //letters that are in the word, but user put in wrong spot
  char partial[10];
  //letters that are in the correct spot
  char correct[10];
} Guesses;

bool tried_letters(Guesses* g, char* guess, char* secret);

bool score_guess(char *secret, char *guess, char *result, Guesses* g);

bool valid_guess(char *guess, char **vocabulary, size_t num_words, Guesses* g, char* secret);

char **load_vocabulary(char *filename, size_t *num_words);

void free_vocabulary(char **vocabulary, size_t num_words);

// Idea for the UNUSED macro from Stack Overflow user mtvec. Thanks!
// https://stackoverflow.com/a/3599170
#define UNUSED(x) (void)(x)
