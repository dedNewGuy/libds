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
	
	queue_t *queue = queue_new(10);
	assert(queue != NULL);
	assert(queue->read_pointer == 5);
	assert(queue->write_pointer == queue->read_pointer);
	assert(queue->capacity == 10);

	int queue1 = 5;
	enqueue(queue, &queue1);

	int queue2 = 10;
	enqueue(queue, &queue2);

	assert(queue->write_pointer == 7);
	assert(queue->read_pointer == 5);

	void *deq1 = dequeue(queue);
	if (deq1 != NULL)
	{
		assert(*(int *)(deq1) == 5);
	}

	assert(queue->write_pointer == 7);
	assert(queue->read_pointer == 6);

	void *peek1 = queue_peek(queue);
	if (peek1 != NULL)
	{
		assert(*(int *)(peek1) == 10);
	}
	
 	return 0;
}
