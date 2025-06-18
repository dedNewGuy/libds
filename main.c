#include <stdio.h>

#include "libds.h"

int main()
{
	
	stack_int *my_stack = init_stack_int(5);

	printf("%d\n", my_stack->stack[0]);

	free_stack_int(my_stack);
	
 	return 0;
}
