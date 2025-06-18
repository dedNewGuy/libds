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

/* RING BUFFER IMPLEMENTATION */

ring_buffer_t *ring_buffer_new(int capacity)
{
	ring_buffer_t *queue = (ring_buffer_t *)malloc(sizeof(ring_buffer_t));
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

int is_ring_buffer_full(ring_buffer_t *ring_buffer)
{
	return ring_buffer->size == ring_buffer->capacity;
}

void ring_buffer_put(ring_buffer_t *ring_buffer, void *item)
{
	ring_buffer->values[ring_buffer->write_pointer] = item;
	
	if (is_ring_buffer_full(ring_buffer)) {
		ring_buffer->read_pointer = (ring_buffer->read_pointer + 1) % ring_buffer->capacity;
	} else {
		ring_buffer->size++;
	}
	
	ring_buffer->write_pointer = (ring_buffer->write_pointer + 1) % ring_buffer->capacity;
}

int is_ring_buffer_empty(ring_buffer_t *ring_buffer)
{
	return ring_buffer->size == 0;
}

void *ring_buffer_pop(ring_buffer_t *ring_buffer)
{
	if (is_ring_buffer_empty(ring_buffer))
	{
		return NULL;
	}
	int idx = ring_buffer->read_pointer;
	ring_buffer->read_pointer = (ring_buffer->read_pointer + 1) % ring_buffer->capacity;
	ring_buffer->size--;
	return ring_buffer->values[idx];
}

void *ring_buffer_peek(ring_buffer_t *ring_buffer)
{
	if (is_ring_buffer_empty(ring_buffer))
	{
		return NULL;
	}
	int idx = ring_buffer->read_pointer;
	return ring_buffer->values[idx];
}

size_t ring_buffer_size(ring_buffer_t *ring_buffer)
{
	return ring_buffer->size;
}

void destroy_ring_buffer(ring_buffer_t *ring_buffer)
{
	free(ring_buffer->values);
	free(ring_buffer);
}
