#include "monty.h"

void monty_pall(stack_t **stack, unsigned int line_number);
void monty_push(stack_t **stack, unsigned int line_number);

/**
 * monty_push - push into a stack, queue
 * @stack: stack to operate on
 * @line_number: line number of the monty script
 *
 * Return: nothing
 */

void monty_push(stack_t **stack, unsigned int line_number)
{
	stack_t *tmp, *new;
	int i;

	new = malloc(sizeof(stack_t));
	if (new == NULL)
	{
		set_op_tok_error(malloc_error());
		return;
	}

	if (op_toks[1] == NULL)
	{
		set_op_tok_error(no_int_error(line_number));
		return;
	}

	for (i = 0; op_toks[1][i]; i++)
	{
		if (op_toks[1][i] == '-' && i == 0)
			continue;
		if (op_toks[1][i] < '0' || op_toks[1][i] > '9')
		{
			set_op_tok_error(no_int_error(line_number));
			return;
		}
	}
	new->n = atoi(op_toks[1]);

	if (check_mode(*stack) == STACK) /* STACK mode insert at front */
	{
		tmp = (*stack)->next;
		new->prev = *stack;
		new->next = tmp;
		if (tmp)
			tmp->prev = new;
		(*stack)->next = new;
	}
	else /* QUEUE mode insert at end */
	{
		tmp = *stack;
		while (tmp->next)
			tmp = tmp->next;
		new->prev = tmp;
		new->next = NULL;
		tmp->next = new;
	}
}

/**
 * monty_pall - prints all the elements of the stack
 * @stack: the stack to print
 * @line_number: line number of the monty script
 *
 * Return: nothin
 */

void monty_pall(stack_t **stack, unsigned int line_number)
{
	stack_t *tmp = (*stack)->next;

	while(tmp)
	{
		printf("%i\n", tmp->n);
		tmp = tmp->next;
	}

	(void)line_number;
}
