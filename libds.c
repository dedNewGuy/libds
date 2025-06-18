#include "libds.h"

#include <stdlib.h>
#include <assert.h>
#include <stdio.h>


stack_t *stack_new(void)
{
	stack_t *stack = (stack_t *)malloc(sizeof(stack_t));
	assert(stack != NULL);
	size_t capacity = 10;
	void **values = malloc(capacity * sizeof(void*));
	assert(values != NULL);
	stack->values = values;
	stack->pointer = 0;
	stack->capacity = capacity;
	return stack;
}

void stack_destroy(stack_t *stack)
{
	free(stack->values);
	free(stack);
}

void stack_push(stack_t *stack, void *item)
{
	if (stack->pointer >= (int)stack->capacity)
	{
		size_t capacity = stack->capacity + 10;
		void **values_new = realloc(stack->values, capacity * sizeof(void *));
		if (values_new == NULL)
		{
			free(stack->values);
			perror("libds");
			return;
		}
		else
		{
			stack->values = values_new;
			stack->capacity = capacity;
		}
	}
	stack->values[stack->pointer] = item;
	stack->pointer += 1;
}

void *stack_pop(stack_t *stack)
{
	if (stack->pointer <= 0)
	{
		return NULL;
	}
	stack->pointer -= 1;
	return stack->values[stack->pointer];
}

void *stack_peek(stack_t *stack)
{
	if (stack->pointer <= 0)
	{
		return NULL;
	}
	return stack->values[stack->pointer - 1];
}

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

