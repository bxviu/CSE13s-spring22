# Design Doc hw3

## functions
### str_suffix

For this function I will use a for loop to iterate through the haystack(the input string), and if a char matches with the first char of the needle(the suffix), then I will use a nested for loop to iterate through both the needle and the haystack at the same time, comparing them to make sure they are the same. If they are, and the loop also reaches the end of the haystack length, then this function will return true. Otherwise, it will continue the for loop. Once it reaches the end and is unable to find the needle, then it will return false.
``` 
for i = 0; i < haystack length; i++:
  if haystack[i] is needle[0] and is not null terminator:
    for j = 0; j < needle length; j++:
      if haystack[i+j] != needle[j]:
        return false;
      elif i+j is haystack length:
        return true;
return false;
```  

### dot_product

For this function I will use a for loop to iterate through both arrays, multiply the elements of each array together and add them to a sum variable. Then the sum will be returned once the loop reaches the length of the arrays.
```
float sum = 0;
for i = 0; i < array length; i++:
  sum += array1[i] * array2[i];
return sum;
```

### reduce

For this function I will have a value, called result, that will be updated by iterating through a for loop. The loop will be calling the function that was passed as an argument and updating result. Once the loop reaches the end of the array it will return result.
```
result = initial value;
for i = 0; i < array length; i++:
  result = function(result, array[i]);
return result;
```

### maximum_with_reduce

For this function I will make a helper function, called compare_greater, that compares two values and returns the greater one. Then in maximum, I will return the reduce function with the input of a function pointer to compare_greater. 
```
compare_greater(a,b)
return (a > b) ? a : b;

max_with_reduce
return reduce(array, length, compare_greater, INT_MIN);
```

### sum_positive_with_reduce

For this function I will make a helper function, called add_positive, that checks if the 2nd parameter is positive and adds it to the 1st parameter and then returns the result. If not, then it will just return the first parameter. Then in sum_positive, I will return the reduce function with a function pointer to add_positive.
```
add_positive(a,b)
return (b > 0) ? a+b : a;

sum_positive_with_reduce
return reduce(array, length, add_positive, 0);
```
