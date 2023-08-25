#include "monty.h"

int check_mode(stack_t *stack);
int init_s(stack_t **stack);
void free_s(stack_t **stack);

/**
 * free_s - frees a stack
 * @stack: stack to free
 *
 * Return: void
 */

void free_s(stack_t **stack)
{
	stack_t *current;

	while ((*stack))
	{
		current = (*stack);
		(*stack) = (*stack)->next;
		free(current);
	}
}

/**
 * init_s - initiates a stack
 * @stack: the stack to initialize
 *
 * Return: 1 on success, 0 else
 */

int init_s(stack_t **stack)
{
	stack_t *s = malloc(sizeof(stack_t));

	if (s == NULL)
	{
		fprintf(stderr, "Error: malloc failed\n");
		exit(EXIT_FAILURE);
	}

	(*stack)->n = STACK;
	(*stack)->next = NULL;
	(*stack)->prev = NULL;

	(*stack) = s;
	return (1);
}

/**
 * check_mode - check if stack
 * @stack: the stack to check
 *
 * Return: 1 on success, 0 else
 */

int check_mode(stack_t *stack)
{
	if (stack->n == STACK)
		return (1);
	if (stack->n == QUEUE)
		return (0);
	return (2);
}
