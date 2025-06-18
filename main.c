#include <stdio.h>

#include "libds.h"

int main()
{
	
	stack_t *stack = stack_new();

	printf("%d\n", stack->pointer);

	stack_destroy(stack);
	
 	return 0;
}
