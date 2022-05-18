# Design Doc hw4

## functions
### score_guess

This function will need to take in the user's input and compare it with the actual word. It will need to iterate through the input word to see if any letters are in the actual word, as well as checking if the letters are in the correct spots. There will be a pointer to a result string that will provide the use more information about thier guess. For each letter, if it is not in the actual word, it is replaced with an x. If a letter is in the actual word, but not in the correct location, a y will be placed instead. If the letter is in the correct spot, a g will be placed. It will return false, unless the input word matches the actual word.
```
if (!strcmp(guess,secret)){
  return true;
} 
for (int i = 0; guess[i] != \0; i++){
  if (guess[i] == secret[i]){
    result[i] = g;
  }
  elif (strchr(secret,guess[i]) != &guess[i]){
    result[i] = y;
  }
  else {
    result[i] = x;
  }
} 
return false;
```  

### valid_guess

This function will check if the input is a word in the vocabulary list that is loaded. It will have to iterate through each word and check if it matches one of them. If it doesn't the function will return false. Otherwise it returns true.
```
for (int i = 0; i < num_words; i++){
  if (!strcmp(guess,vocabulary[i])){
    return true;
  }
}
return false;
```

### load_vocabulary

This function will return an array of words from the vocabulary file. It will need to open the inputted filename, then keep reading words from it, and increasing the size of the array with realloc once the array gets full.
```
char **out = NULL;
FILE* infile;
char word[6];
infile = fopen(filename, "r");
int size = 0;
char* stream;
do {
  stream = fgets(word,6,infile);
  out = realloc(out, 6);
  out[size] = stream;
  size++;
}
while(stream != NULL));
num_words = size;
fclose(&vocabulary);
return out;
```

### free_vocabulary

This function will free the inputted vocabulary array. It needs to iterate through each word, freeing them, all the way until the inputted length of the array. The the pointer to the array will be freed as well.
```
for (int i = 0; i < num_words; i++){
  free(vocabulary[i]);
}
free(vocabulary);
```
