# Design Doc hw7

## functions
### score_letter

For this function, it will initialize an int count to keep track of the words containing the inputted letter. Then the function will use a loop to iterate through the inputted voacabulary. For each word in the vocabulary, the function will use strchr to check if the letter is in the word. If the letter is found, a count will be incremented by 1. Once the loop reaches the end, count is returned.  
```
int count = 0;
for (size_t i = 0; i < num_words; i++){
  if (strchr(vocabulary[i],letter)){
    count++;
  }
}
return count;
```  

### score_word

For this function, it will also initialize an int count for the score of the word. The function will iterate through the inputted word, adding the sum of each letter from letter_scores in the array. To make sure each letter is counted once, the function will use strchr to check if the pointer is the same, and if it isn't, then it means it is a duplicate letter which does not need to be added to the score.
```
int count = 0;
for (int i = 0; word[i] != '\0'; i++){
  if (strchr(word,word[i]) == &word[i]) {
    count += letter_scores[((int)word[i])-97];  
  }
}
return count;
```

### filter_vocabulary_gray

This function will iterate through the vocab. For each word, the function will once again use strchr to see if the letter is in the word. If strchr returns a pointer, that means the letter is in the word. If the letter is in the word, the word will be freed, and it's pointer will be set to NULL. This function will also keep count of the removed words, so it will increment by 1 for every removal. The count will be returned at the end of the function.
```
int count = 0;
for (size_t i = 0; i < num_words; i++){
  if (strchr(vocabulary[i],letter)){
    free(vocabulary[i]);
    vocabulary[i] = NULL;
    count++;
  }
}
return count;
```

### filter_vocabulary_yellow

Like the previous function, this one will also iterate through the vocabulary. It will iterate through the word using strchr to see if the word contains the letter. If it doesn't then the word will be freed and it's pointer set to NULL. If the word does contain the letter, then the function will check if the letter appears at the inputted position, and if it does, then the word will also be freed and pointer set to NULL. This function will also keep a count and return the amount of words that were removed.
```
int count = 0;
for (size_t i = 0; i < num_words; i++){
  if (!strchr(vocabulary[i],letter)){
    free(vocabulary[i]);
    vocabulary[i] = NULL;
    count++;
  }
  else if (*((&vocabulary[i])+position) == letter){
    free(vocabulary[i]);
    vocabulary[i] = NULL;
    count++;
  }
}
return count;
```

### filter_vocabulary_green

Again, like the past two functions, this function will iterate through the vocabulary. For each word, it will check if the inputted letter does not appear in the inputted position. If this is true, then the word will be freed and pointer set to NULL. The amount of words is also tracked and will be returned at the end of the function.
```
int count = 0;
for (size_t i = 0; i < num_words; i++){
  if (*((&vocabulary[i])+position) != letter){
    free(vocabulary[i]);
    vocabulary[i] = NULL;
    count++;
  }
}
return count;
```
