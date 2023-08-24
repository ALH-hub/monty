#include "monty.h"

/**
 * get_opcode - get the opcode to run
 * @opcode: the opcode to search for
 *
 * Description: searches for the opcode provided
 * Return: nothin
 */

void (*get_opcode(char *opcode)(stack_t **stack, unsigned int line_number))
{
	instruction_t op_funcs[] = {
		{"push", monty_push},
		{"pop", monty_pop},
		{"pint", monty_pint},
		{"pall", monty_pall},
		{"swap", monty_swap},
		{"add", monty_add},
		{"nop", monty_nop},
		{NULL, NULL}
	}
	int i;

	for (i = 0; op_funcs[i]; i++)
	{
		if (strcmp(op_funcs[i].opcode, opcode) == 0)
			return (op_funcs[i].f);
	}

	return (NULL);
}
