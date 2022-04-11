# Design Doc hw2

## functions
### next_collatz_number

For this function, I will modulo the input number by 2, and if the result is 0, then I will return half the input number. If the result is 1, then I will return the input number times 3, plus 1.

### count_collatz_steps

I will initialize a variable, num, that takes the input number. I will also initialize a variable, count, to count the steps. Using num, I will use a while loop that keeps putting the num through the next_collatz_number function until num is 1, while also counting the amount of loops. Once num is 1, I will return count.

### maximum

I will initialize a variable called max with the first element in the array, to hold the current max value. I will iterate through the array with a for loop that loops until it reaches the input length. Once the for loop ends, I will return max.

### sum_positive

I will initialize a variable called sum with 0. Then I will use a for loop to iterate through the array, and stopping once it reaches the input length. In the loop, it will check if the current array element is greater than 0, and if so, it will add the value to the sum. After the loop ends, it will return the sum.

## count_negative

I will initialize a variable called count with 0. Like sum_positive, I will use a for loop to iterate through the array, and stopping once it reaches the input size. In the loop, it will check if the current array element is less than 0, and if so, it will increment count by 1. After the loop ends, it will return the count.
