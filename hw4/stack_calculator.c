#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "stack_calculator.h"

// Allocate a new Stack struct and return a pointer to it.
Stack *stack_create(void) {
  // this one is complete, no need to change it!
  Stack *out;
  out = (Stack *)calloc(1, sizeof(Stack));
  return out;
}

// Add a new node at the front of the stack. Return false if we are unable to do
// so (eg, if memory allocation fails).
bool stack_push(Stack *s, CalculatorItem item) {
  // your code here
  Node *newNode;
  newNode = (Node*)malloc(sizeof(Node));
  if (newNode == NULL) return false;
  if (stack_empty(s)){ newNode->next = NULL; } 
  else { newNode->next = s->top; }
  newNode->item = item;
  s->top = newNode;
  return true;
}

// Pop the stack and put the result into the output pointer.
// return false if the stack is NULL or if it is empty.
bool stack_pop(Stack *s, CalculatorItem *output) {
  // your code here
  if (stack_empty(s)) return false;
  *output = s->top->item;
  Node* deleteThis = s->top;
  s->top = s->top->next;
  free(deleteThis);
  return true;
}

// Returns true if the specified stack is empty.
bool stack_empty(Stack *s) {
  // your code here
  return s->top == NULL;
}

// Free all of the memory used by this stack, including its linked list.
// When you are done, set the pointer to NULL.
void stack_delete(Stack **s) {
  // your code here
  CalculatorItem temp;
  //while (!stack_empty((*s))){
  while (stack_pop(*s, &temp));
  //stack_pop(*s, &temp);}
  free(*s);
  *s = NULL;
}

// Returns true if we were able to successfully perform the computation step,
// and false if there was an error of some kind.
bool stack_compute_step(Stack *s, CalculatorItem item) {
  // your code here
  if (item.type == NUMBER){ stack_push(s, item); }
  else {
      CalculatorItem a;
      CalculatorItem b;
      if (!stack_pop(s, &a)){ return false; }
      if (!stack_pop(s, &b)){ return false; }
      CalculatorItem result;
      if (item.type == ADD){
        result.value = a.value + b.value;
      }
      else if (item.type == SUBTRACT){
        result.value = b.value - a.value;
      }
      else if (item.type == MULTIPLY){
        result.value = a.value * b.value;
      }
      else {
	if (!a.value){ return false; }
        result.value = b.value / a.value;
      }
    result.type = NUMBER;
    stack_push(s, result);
  }
  return true;
}
