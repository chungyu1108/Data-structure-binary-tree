/*
 * This file contains a simple implementation of a linked list-based stack.
 * See the documentation below for more information on the individual functions
 * in this implementation.  You should not modify anything in this file.
 */

#include <stdlib.h>
#include <assert.h>

#include "stack.h"
#include "list.h"

/*
 * This is the structure that represents a stack.  It contains a single field
 * representing a linked list that is used as the underlying data storage for
 * the stack.
 */
struct stack {
  struct list* list;
};

/*
 * This function allocates and initializes a new, empty stack and returns a
 * pointer to it.
 */
struct stack* stack_create() {
  struct stack* stack = malloc(sizeof(struct stack));
  stack->list = list_create();
  return stack;
}

/*
 * This function frees the memory associated with a stack.  Note that it does
 * not free any memory allocated to the pointer values stored in the stack.
 * This is the responsibility of the caller.
 *
 * Params:
 *   stack - the stack to be destroyed.  May not be NULL.
 */
void stack_free(struct stack* stack) {
  assert(stack);
  list_free(stack->list);
  free(stack);
}

/*
 * This function indicates whether a given stack is currently empty.  It
 * returns 1 if the specified stack is empty (i.e. contains no elements) and
 * 0 otherwise.
 *
 * Params:
 *   stack - the stack whose emptiness is being questioned.  May not be NULL.
 */
int stack_isempty(struct stack* stack) {
  assert(stack);
  return list_isempty(stack->list);
}

/*
 * This function pushes a new value onto a given stack.  The value to be
 * pushed is specified as a void pointer.
 *
 * Params:
 *   stack - the stack onto which a value is to be pushed.  May not be NULL.
 *   val - the value to be pushed.  Note that this parameter has type void*,
 *     which means that a pointer of any type can be passed.
 */
void stack_push(struct stack* stack, void* val) {
  assert(stack);
  list_insert(stack->list, val);
}

/*
 * This function returns the value stored at the top of a given stack *without*
 * removing that value.
 *
 * Params:
 *   stack - the stack from which to query the top value.  May not be NULL.
 */
void* stack_top(struct stack* stack) {
  assert(stack);
  return list_head(stack->list);
}

/*
 * This function pops a value from a given stack and return the popped value.
 *
 * Params:
 *   stack - the stack from which a value is to be popped.  May not be NULL.
 *
 * Return:
 *   This function returns the value that was popped.
 */
void* stack_pop(struct stack* stack) {
  assert(stack);
  void* head = list_head(stack->list);
  list_remove_head(stack->list);
  return head;
}
