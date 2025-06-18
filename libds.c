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

queue_t *queue_new(int capacity)
{
	queue_t *queue = (queue_t *)malloc(sizeof(queue_t));
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

int is_queue_full(queue_t *queue)
{
	return queue->size == queue->capacity;
}

void enqueue(queue_t *queue, void *item)
{
	queue->values[queue->write_pointer] = item;
	
	if (is_queue_full(queue)) {
		queue->read_pointer = (queue->read_pointer + 1) % queue->capacity;
	} else {
		queue->size++;
	}
	
	queue->write_pointer = (queue->write_pointer + 1) % queue->capacity;
}

int is_queue_empty(queue_t *queue)
{
	return queue->size == 0;
}

void *dequeue(queue_t *queue)
{
	if (is_queue_empty(queue))
	{
		return NULL;
	}
	int idx = queue->read_pointer;
	queue->read_pointer = (queue->read_pointer + 1) % queue->capacity;
	queue->size--;
	return queue->values[idx];
}

void *queue_peek(queue_t *queue)
{
	if (is_queue_empty(queue))
	{
		return NULL;
	}
	int idx = queue->read_pointer;
	return queue->values[idx];
}

size_t queue_size(queue_t *queue)
{
	return queue->size;
}

void queue_destroy(queue_t *queue)
{
	free(queue->values);
	free(queue);
}
