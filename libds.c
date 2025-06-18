#include "libds.h"
#include <stdlib.h>

/* -- STACK IMPLEMENTATION -- */

stack_int *init_stack_int(size_t size)
{
	int *stack = calloc(size, sizeof(int));
	int head = stack[0];

	stack_int *le_stack = malloc(sizeof(stack_int));
	le_stack->stack = stack;
	le_stack->head = head;
	le_stack->length = 0;
	le_stack->capacity = size;

	return le_stack;
}

void free_stack_int(stack_int *stack)
{
	free(stack->stack);
	free(stack);
}

/* void stack_push_int(stack_int stack, void *item) */
/* { */
/* } */

/* void *stack_pop_int(stack_int stack) */
/* { */
/* } */

/* void *stack_peek_int(stack_int stack) */
/* { */
/* } */

/* void is_stack_int_empty(stack_int stack) */
/* { */
/* } */

/* size_t stack_int_size(stack_int stack) */
/* { */
/* } */

