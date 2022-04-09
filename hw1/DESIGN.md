# My plan for the four functions in this homework is to work on one at a time before moving on to the next one.

## hw1.c
### area_of_disk

I plan to use the constant M_PI that was told about in the hw1 instructions. Since it is the area, this function will return a number, so maybe the return type will be int or float.

### area_of_ring

I could probably call the area_of_disk function 2 times. 1 for the large disk and 1 for the small disk. Then I could subtract their values and return the result, which will be a number.

### bigger_minus_smaller

I could probably just return the absolute value of the first parameter minus the second parameter. However, just to be safe with the autograder, I will just follow the instructions by comparing the values and subtracting them.

### value_in_range

I probably just need to compare if the value is both less than or equal to the upper bound and greater than or equal to the lower bound. Then I would return true if it is indeed true.

## caat.c

I will use what I remember from the lecture last Friday where the teacher used putchar and getchar. I need to reprint whatever is inputted, and then when a vowel is inputted, the program should reprint it twice. To do this I will most likely use some if statements to check if putchar is a vowel.
