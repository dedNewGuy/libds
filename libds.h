#ifndef LIBDS_H
#define LIBDS_H

#include <stddef.h>

/* -- NODE -- */
typedef struct node_t node_t;

typedef struct node_t {
	void *value;
	node_t *next;
} node_t;

/* -- STACK -- */

struct stack_int {
	int *stack;
	int head;
	int length;
	size_t capacity;
};

typedef struct stack_int stack_int;

stack_int *init_stack_int(size_t size);
void stack_push_int(stack_int stack, void *item);
void *stack_pop_int(stack_int stack);
void *stack_peek_int(stack_int stack);
void is_stack_int_empty(stack_int stack);
size_t stack_int_size(stack_int stack);
void free_stack_int(stack_int *stack);

#endif // LIBDS_H
