#include "libds.h"

#include <stdlib.h>
#include <stdio.h>

/* -- STACK IMPLEMENTATION -- */

stack_t *stack_new(void)
{
	stack_t *stack = (stack_t *)malloc(sizeof(stack_t));
	if (stack == NULL)
	{
		perror("libds: failed to alloc stack");
		return NULL;
	}
	size_t capacity = 10;
	void **values = malloc(capacity * sizeof(void*));
	if (values == NULL)
	{
		perror("libds: failed to alloc stack");
		free(stack);
		return NULL;
	}
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

int stack_push(stack_t *stack, void *item)
{
	if (stack->pointer >= stack->capacity)
	{
		size_t capacity = stack->capacity * 2;
		void **values_new = realloc(stack->values, capacity * sizeof(void *));
		if (values_new == NULL)
		{
			perror("libds: failed to realloc stack");
			return -1;
		}
		else
		{
			stack->values = values_new;
			stack->capacity = capacity;
		}
	}
	stack->values[stack->pointer] = item;
	stack->pointer += 1;
	return 0;
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

/* QUEUE RING IMPLEMENTATION */

queue_ring_t *queue_ring_new(int capacity)
{
	queue_ring_t *queue = (queue_ring_t *)malloc(sizeof(queue_ring_t));
	if (queue == NULL)
	{
		perror("libds: failed to alloc queue");
		return NULL;
	}
	void **values = malloc(capacity * sizeof(void*));
	if (values == NULL)
	{
		perror("libds: failed to alloc queue");
		free(queue);
		return NULL;
	}
	queue->values = values;
	queue->read_pointer = 0;
	queue->write_pointer = queue->read_pointer;
	queue->size = 0;
	queue->capacity = capacity;
	return queue;
}

int is_queue_ring_full(queue_ring_t *queue_ring)
{
	return queue_ring->size == queue_ring->capacity;
}

void enqueue_ring(queue_ring_t *queue_ring, void *item)
{
	queue_ring->values[queue_ring->write_pointer] = item;
	
	if (is_queue_ring_full(queue_ring)) {
		queue_ring->read_pointer = (queue_ring->read_pointer + 1) % queue_ring->capacity;
	} else {
		queue_ring->size++;
	}
	
	queue_ring->write_pointer = (queue_ring->write_pointer + 1) % queue_ring->capacity;
}

int is_queue_ring_empty(queue_ring_t *queue_ring)
{
	return queue_ring->size == 0;
}

void *dequeue_ring(queue_ring_t *queue_ring)
{
	if (is_queue_ring_empty(queue_ring))
	{
		return NULL;
	}
	int idx = queue_ring->read_pointer;
	queue_ring->read_pointer = (queue_ring->read_pointer + 1) % queue_ring->capacity;
	queue_ring->size--;
	return queue_ring->values[idx];
}

void *queue_ring_peek(queue_ring_t *queue_ring)
{
	if (is_queue_ring_empty(queue_ring))
	{
		return NULL;
	}
	int idx = queue_ring->read_pointer;
	return queue_ring->values[idx];
}

size_t queue_ring_size(queue_ring_t *queue_ring)
{
	return queue_ring->size;
}

void queue_ring_destroy(queue_ring_t *queue_ring)
{
	free(queue_ring->values);
	free(queue_ring);
}
