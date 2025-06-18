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

struct __queue_t {
	void **values;
	size_t write_pointer; // WRITE INDEX
	size_t read_pointer; // READ INDEX
	size_t capacity;
};

typedef struct __queue_t queue_t;

queue_t *queue_new(int capacity);
void enqueue(queue_t *queue, void *item);
void *dequeue(queue_t *queue);
void *queue_peek(queue_t *queue);
int is_queue_empty(queue_t *queue);
void queue_destroy(queue_t *queue);

#endif // LIBDS_H_
