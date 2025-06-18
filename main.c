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

	/* Testing Queue Ring */
	
	queue_ring_t *queue_ring = queue_ring_new(10);
	assert(queue_ring != NULL);
	assert(queue_ring->read_pointer == 0);
	assert(queue_ring->write_pointer == queue_ring->read_pointer);
	assert(queue_ring->capacity == 10);
	assert(queue_ring->size == 0);	

	int queue_ring1 = 5;
	enqueue_ring(queue_ring, &queue_ring1);

	int queue_ring2 = 10;
	enqueue_ring(queue_ring, &queue_ring2);

	assert(queue_ring->write_pointer == 2);
	assert(queue_ring->read_pointer == 0);
	assert(queue_ring->size == 2);

	void *deq1 = dequeue_ring(queue_ring);
	if (deq1 != NULL)
	{
		assert(*(int *)(deq1) == 5);
	}

	assert(queue_ring->write_pointer == 2);
	assert(queue_ring->read_pointer == 1);
	assert(queue_ring->size == 1);
	
	void *peek1 = queue_ring_peek(queue_ring);
	if (peek1 != NULL)
	{
		assert(*(int *)(peek1) == 10);
	}

	queue_ring_destroy(queue_ring);
	
 	return 0;
}
