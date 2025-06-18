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

struct __ring_buffer_t {
	void **values;
	size_t write_pointer; // WRITE INDEX
	size_t read_pointer; // READ INDEX
	size_t size;
	size_t capacity;
};

typedef struct __ring_buffer_t ring_buffer_t;

ring_buffer_t *ring_buffer_new(int capacity);
void ring_buffer_put(ring_buffer_t *ring_buffer, void *item);
void *ring_buffer_pop(ring_buffer_t *ring_buffer);
void *ring_buffer_peek(ring_buffer_t *ring_buffer);
size_t ring_buffer_size(ring_buffer_t *ring_buffer);
int is_ring_buffer_full(ring_buffer_t *ring_buffer);
int is_ring_buffer_empty(ring_buffer_t *ring_buffer);
void destroy_ring_buffer(ring_buffer_t *ring_buffer);

#endif // LIBDS_H_
