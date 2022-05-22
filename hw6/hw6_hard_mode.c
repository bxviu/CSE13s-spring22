#include "wordle_game_hard_mode.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Once your other functions are working, please revert your main() to its
// initial state, but please feel free to change it, during development. You'll
// want to test out each individual function!
int main(void) {
  char **vocabulary;
  size_t num_words;
  int num_guesses = 0;

  srand(time(NULL));

  // load up the vocabulary and store the number of words in it.
  vocabulary = load_vocabulary("vocabulary.txt", &num_words);

  // Randomly select one of the words from the file to be today's SECRET WORD.
  int word_index = rand() % num_words;
  char *secret = vocabulary[word_index];
  //printf("word is: %s\n", secret);
  // input buffer -- we'll use this to get a guess from the user.
  char guess[80];
  Guesses g = {{""},{""},{-1,-1,-1,-1,-1,'\0'}};
  // buffer for scoring each guess.
  char result[6] = {0};
  bool success = false;

  printf("time to guess a 5-letter word! (press ctrl-D to exit)\n");
  while (!success) {
    printf("guess: ");
    if (fgets(guess, 80, stdin) == NULL) {
      break;
    }
    
    // Whatever the user input, cut it off at 5 characters.
    guess[5] = '\0';

    if (!valid_guess(guess, vocabulary, num_words, &g, secret)) {
      printf("not a valid guess\n\n");
      continue;
    } else {
      num_guesses++;
    }
    success = score_guess(secret, guess, result, &g);
    printf("%s\n", guess);
    printf("%s\n", result);
  }

  if (success) {
    printf("you win, in %d guesses!\n", num_guesses);
  }
  //printf("word is: %s\n", secret);
  free_vocabulary(vocabulary, num_words);
  //free(tried);
  return 0;
}
