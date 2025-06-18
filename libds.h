#ifndef LIBDS_H_
#define LIBDS_H_

#include <stddef.h>

/* -- NODE -- */
typedef struct node_t node_t;

typedef struct node_t {
	void *value;
	node_t *next;
} node_t;

/* -- STACK -- */

struct __stack_t {
	void **values;
	size_t pointer;
	size_t capacity;
};

typedef struct __stack_t stack_t;

stack_t *stack_new(void);
int stack_push(stack_t *stack, void *item);
void *stack_peek(stack_t *stack);
void *stack_pop(stack_t *stack);
void stack_destroy(stack_t *stack);

/* QUEUE (RING BUFFER) */

struct __queue_ring_t {
	void **values;
	size_t write_pointer; // WRITE INDEX
	size_t read_pointer; // READ INDEX
	size_t size;
	size_t capacity;
};

typedef struct __queue_ring_t queue_ring_t;

queue_ring_t *queue_ring_new(int capacity);
void enqueue_ring(queue_ring_t *queue_ring, void *item);
void *dequeue_ring(queue_ring_t *queue_ring);
void *queue_ring_peek(queue_ring_t *queue_ring);
size_t queue_ring_size(queue_ring_t *queue_ring);
int is_queue_ring_full(queue_ring_t *queue_ring);
int is_queue_ring_empty(queue_ring_t *queue_ring);
void queue_ring_destroy(queue_ring_t *queue_ring);

#endif // LIBDS_H_
