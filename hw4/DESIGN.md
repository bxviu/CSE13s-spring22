# Design Doc hw4

## functions
### stack_push

For stack_push I will create a Node struct. For it's CalculatorItem, it will call malloc to store the item. Then it will put the new Node on the front of the inputted stack, by changing the stack's top pointer to the new Node created. In the new Node, it will point to the node that was previously in the front. If malloc returns null, then the function will return false, otherwise it will return true.
``` 
Node *newNode;
newNode = (Node*)malloc(sizeof(Node));
if (newNode == null) { return false; }
newNode->next = s.top;
newNode->item = item;
s.top = newNode;
return true;
```  

### stack_pop

For stack_pop the function will save the Calculator item into the output pointer, then free the node on the top of the inputted stack. If the stack is null or empty, the function will return false, otherwise it will return true.
```
if (s.top == null) { return false; }
output = s.top->item;
deleteThis = s.top;
s.top = deleteThis->next;
free(deleteThis);
return true;
```

### stack_empty

For stack_empty the function will check if the inputted stack's top is null. If it is null, then the function will return true, otherwise it will return false;
```
return s.top != null;
```

### stack_delete

For stack_delete, the function will pop all the nodes in the stack using a while loop that loops until s.top is null. Then the function will free the Stack struct and set it's pointer to null.
```
while (s.top != null){
	stack_pop(*s.top);
}
free(*s);
s = null;
```

### stack_compute_step

For stack_compute_step, the function will put the Calculator item on the stack if its type is a number. If the item's type is an operator, then it will pop 2 items from the stack, and perform the calculation with them, using the operator. Once it gets the result, it will push the result back onto the stack. If 2 values can't be popped from the stack, or there is division by 0, then the function will return false. Otherwise it will return true.
```
if (item.type == number){ stack_push(s, item); }
else if (item.type == add, subtract, multiply, or divide){
	float* a;
	float* b;
	if (!stack_pop(s, a)){ return false; }
        if (!stack_pop(s, b)){ return false; }
	if (item.type == add){
		CalculatorItem result;
		result.value = a + b;
		result.type = number;
		stack_push(s, result); 
	}
	subtract is similar except it is b - a.
	multiply is a * b
	divide is b / a
}
return true;
```
