#include <stdio.h>
#include <assert.h>

#include "libds.h"

int main()
{

	/* Test stack */
	stack_t *stack = stack_new();
	
	int item1 = 5;
	int item2 = 10;
	
	if (stack_push(stack, &item1) == 0)
		printf("Pushing: %d\n", item1);
	
	if (stack_push(stack, &item2) == 0)
		printf("Pushing: %d\n", item2);	
	
	int *head = stack_peek(stack);
	
	printf("Head: %d\n", *head);
	
	void *raw = stack_pop(stack);
	if (raw == NULL)
	{
		int *popped = (int *)raw;
		printf("Popped stack\n");
		printf("Popped: %d\n", *popped);
	}
	
	head = stack_peek(stack);
	printf("Head: %d\n", *head);

	stack_destroy(stack);

	/* Testing Queue */
	
	queue_t *queue = queue_new();
	assert(queue != NULL);
	assert(queue->pointer == 0);
	assert(queue->capacity == 10);

 	return 0;
}
