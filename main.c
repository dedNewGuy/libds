#include <stdio.h>

#include "libds.h"

int main()
{

	/* Test stack */
	stack_t *stack = stack_new();
	
	int item1 = 5;
	int item2 = 10;
	
	stack_push(stack, &item1);
	stack_push(stack, &item2);
	
	int *head = stack_peek(stack);
	
	printf("%d\n", *head);
	
	int popped = *(int *)(stack_pop(stack));
	
	head = stack_peek(stack);
	printf("%d\n", *head);
	printf("Popped: %d\n", popped);

	stack_destroy(stack);

 	return 0;
}
