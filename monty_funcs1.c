#include "monty.h"

void monty_push(stack_t **stack, unsigned int line_number)
{
	stack_t *new, *tmp;
	int i;

	new = malloc(sizeof(stack_t));
	if (new == NULL)
	{
		fprintf(stderr, "Error: malloc failed\n");
		exit(EXIT_FAILURE);
	}

	if (op_toks[1] == NULL)
	{
		fprintf(stderr, "L%u: unknown instruction %s\n", line_number, op_toks[0]);
		exit(EXIT_FAILURE);
	}

	for (i = 0; op_toks[1][i]; i++)
	{
		if (op_toks[1][i] == '-' && i = 0)
			continue;
		if (op_toks[1][i] < '0' && op_toks[1][i] > '9')
		{
			fprintf(stderr, "L%u: usage: push integer\n", line_number);
			exit(EXIT_FAILURE);
		}
	}

	new->n = atoi(op_toks[1]);

	if (check_mode(*stack) == 1)
	{
		tmp = (*stack)->next;
		new->prev = (*stack);
		new->next = tmp;
		if (tmp)
			tmp->prev = new;
		(*stack)->next = new;
	}
	else
	{
		tmp = *stack;
		while (tmp->next)
			tmp = tmp->next;
		new->prev = tmp;
		new->next = NULL;
		tmp->next = nw;
	}
}
