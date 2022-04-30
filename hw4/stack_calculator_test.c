#include <stdio.h>

#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "stack_calculator.h"

bool approximately_equal(double a, double b) {
  // difference is less than 0.001?
  return fabs(a - b) < 0.001;
}

void should_be_equal(const char *message, double expected, double actual) {
  printf("%s\n", message);
  printf("%s: wanted %f, got %f\n",
         approximately_equal(expected, actual) ? "SUCCESS" : "FAILURE",
         expected, actual);
}

void should_be_exactly_equal(const char *message, int expected, int actual) {
  printf("%s\n", message);
  printf("%s: wanted %d, got %d\n",
         (expected == actual) ? "SUCCESS" : "FAILURE", expected, actual);
}

void ptr_should_be_equal(const char *message, void *expected, void *actual) {
  printf("%s\n", message);
  printf("%s: wanted %p, got %p\n",
         (expected == actual) ? "SUCCESS" : "FAILURE", expected, actual);
}

int main(void) {

  printf("**********************\n");
  printf("tests for stack_push\n");
  Stack *stack1 = stack_create();
  CalculatorItem five = {NUMBER, 5.0};
  CalculatorItem six = {NUMBER, 6.0};

  stack_push(stack1, five);
  stack_push(stack1, six);
  should_be_equal("second stack element should be 5",
                  stack1->top->next->item.value, 5.0);
  should_be_equal("first stack element should be 6", stack1->top->item.value,
                  6.0);

  printf("\n**********************\n");
  printf("tests for stack_pop\n");
  CalculatorItem output;
  bool result;

  result = stack_pop(stack1, &output);
  should_be_equal("popped something, expect 6", output.value, 6.0);
  should_be_exactly_equal("expect true", true, result);
  result = stack_pop(stack1, &output);
  should_be_equal("popped something, expect 5", output.value, 5.0);
  should_be_exactly_equal("expect true", true, result);
  result = stack_pop(stack1, &output);
  should_be_exactly_equal("expect false", false, result);

  printf("\n**********************\n");
  printf("tests for stack_empty\n");
  Stack *stack2 = stack_create();
  result = stack_empty(stack2);
  should_be_exactly_equal("expect true", true, result);
  stack_push(stack2, five);
  result = stack_empty(stack2);
  should_be_exactly_equal("expect false", false, result);
  stack_delete(&stack2);
  
  printf("\n**********************\n");
  printf("tests for stack_delete\n");
  // note that we'll also make sure that no memory is leaked, in autograding
  stack_delete(&stack1);
  ptr_should_be_equal("stack1 should be set to NULL", NULL, stack1);

  printf("\n**********************\n");
  printf("tests for stack_compute_step\n");
  Stack *stack3 = stack_create();
  stack_compute_step(stack3, five);
  stack_compute_step(stack3, six);
  should_be_equal("first stack element should be 6", stack3->top->item.value,
                  6.0);
  CalculatorItem plus = {ADD, 0.0};
  stack_compute_step(stack3, plus);
  should_be_equal("first stack element should be 11", stack3->top->item.value,
                  11.0);
  CalculatorItem eleven = {NUMBER, 11.0};
  stack_compute_step(stack3, eleven);
  stack_compute_step(stack3, plus);
  should_be_equal("first stack element should be 22", stack3->top->item.value,
                  22.0);
  stack_compute_step(stack3, eleven);
  CalculatorItem divide = {DIVIDE, 0.0};
  stack_compute_step(stack3, divide);
  should_be_equal("first stack element should be 2", stack3->top->item.value,
                  2.0);
  CalculatorItem two = {NUMBER, 2.0};
  stack_compute_step(stack3, two);
  CalculatorItem multiply = {MULTIPLY, 0.0};
  stack_compute_step(stack3, multiply);
  should_be_equal("first stack element should be 4", stack3->top->item.value,
                  4.0);

  CalculatorItem four = {NUMBER, 4.0};
  stack_compute_step(stack3, four);
  CalculatorItem subtract = {SUBTRACT, 0.0};
  stack_compute_step(stack3, subtract);
  should_be_equal("first stack element should be 0", stack3->top->item.value,
                  0.0);

  result = stack_pop(stack3, &output);
  should_be_equal("popped value should be 0", 0.0, output.value);
  result = stack_empty(stack3);
  should_be_exactly_equal("stack3 should now be empty", true, result);
  
  stack_delete(&stack3);
  
  printf("\n**********************\n");
  printf("test for stack_delete on non-empty stack\n");
  Stack *stack4 = stack_create();
  stack_push(stack4, five);
  stack_push(stack4, four);
  stack_push(stack4, two);
  stack_delete(&stack4);
  ptr_should_be_equal("stack4 should be set to NULL\n", NULL, stack4);
  
  printf("\n**********************\n");
  printf("test for stack_delete and pop on an empty stack\n");
  Stack *stack5 = stack_create();
  result = stack_pop(stack5, &output);
  stack_delete(&stack5);
  ptr_should_be_equal("stack5 should be set to NULL\n", NULL, stack4);
  printf("result after popping an empty stack: %d\n",result);

  printf("\n**********************\n");
  printf("test for stack_compute_step on a stack with not enough numbers\n");
  Stack *stack6 = stack_create();
  stack_push(stack6, five);
  result = stack_compute_step(stack6, subtract);
  printf("return compute on one number: %d\n", result);
  stack_pop(stack6, &output);
  result = stack_compute_step(stack6, plus);
  printf("return compute on empty stack: %d\n", result);
  stack_delete(&stack6);
  
  printf("\n**********************\n");
  printf("test for stack_compute_step on division by 0\n");
  Stack *stack7 = stack_create();
  CalculatorItem zero = {NUMBER, 0.0};
  stack_push(stack7,four);
  stack_push(stack7, five);
  result = stack_compute_step(stack7,divide);
  printf("return of division not by 0: %d\n", result);
  stack_compute_step(stack7, zero);
  result = stack_compute_step(stack7,divide);
  printf("return of division by 0: %d\n", result);
  stack_delete(&stack7);

  return 0;
}
