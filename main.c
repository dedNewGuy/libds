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

	/* Testing Ring Buffer */
 
	ring_buffer_t *ring_buffer = ring_buffer_new(7);
	printf("Write pointer: %ld\n", ring_buffer->write_pointer);
	printf("Read pointer: %ld\n", ring_buffer->read_pointer);
	printf("Ring Buffer Size: %ld\n", ring_buffer->size);
	printf("Ring Buffer Capacity: %ld\n", ring_buffer->capacity);
	
	int items[] = {1, 2, 3, 4, 5, 6, 7};
	for (int i = 0; i < 7; ++i) {
		ring_buffer_put(ring_buffer, &items[i]);
		printf("Ring Buffer Size: %ld\n", ring_buffer->size);
		printf("Write pointer: %ld\n", ring_buffer->write_pointer);
		printf("Read pointer: %ld\n", ring_buffer->read_pointer);
	}
	
	void *peeked = ring_buffer_peek(ring_buffer);
	if (peeked != NULL) {
		int val = *(int *)(peeked);
		printf("Peeked value: %d\n", val);
	}

	int overwrite_demo = 8;
	ring_buffer_put(ring_buffer, &overwrite_demo);

	printf("%d\n", *(int *)(ring_buffer->values[0])); // 8

	peeked = ring_buffer_peek(ring_buffer);
	if (peeked != NULL) {
		int val = *(int *)(peeked);
		printf("Peeked value: %d\n", val);
	}

	void *popped = ring_buffer_pop(ring_buffer);
	if (popped != NULL) {
		int val = *(int *)(popped);
		printf("Popped value: %d\n", val);
	}

	peeked = ring_buffer_peek(ring_buffer);
	if (peeked != NULL) {
		int val = *(int *)(peeked);
		printf("Peeked value: %d\n", val);
	}

	destroy_ring_buffer(ring_buffer);

 	return 0;
}
