#include "monty.h"
#include <stdio.h>

void free_toks(void);
int run_monty(FILE *script);
unsigned int token_arr_len(void);
int is_empty_line(char *line, char *delims);
void (*get_op_func(char *opcode))(stack_t**, unsigned int);

/**
 * is_empty_line - checks if line is empty
 * @line: the line to check
 * @delim: the delimiters
 *
 * Return: 1 if line has only delims, 0 else
 */
int is_empty_line(char *line, char *delims)
{
	int i, j;

	for (i = 0; line[i]; i++)
	{
		for (j = 0; delims[j]; j++)
		{
			if (line[i] == delims[j])
				break;
		}
		if (delims[j] == '\0')
			return (0);
	}

	return (1);
}

/**
 * get_op_func - get the function related to opcode
 * @opcode: opcode concerned
 *
 * Return: pointer to func
 */

void (*get_op_func(char *opcode))(stack_t**, unsigned int)
{
	instruction_t op_funcs[] = {
		{"push", monty_push},
		{"pall", monty_pall},
		{"pint", monty_pint},
		{"pop", monty_pop},
		{"swap", monty_swap},
		{"add", monty_add},
		{"nop", monty_nop},
		{NULL, NULL}
	};
	int i;

	for (i = 0; op_funcs[i].opcode; i++)
	{
		if (strcmp(opcode, op_funcs[i].opcode) == 0)
			return (op_funcs[i].f);
	}

	return (NULL);
}

/**
 * token_arr_len - find the length ot op_toks
 *
 * Return: length of op_toks
 */
unsigned int token_arr_len(void)
{
	unsigned int toks_len = 0;

	while (op_toks[toks_len])
		toks_len++;
	return (toks_len);
}

/**
 * run_monty - run the monty opcode
 * @script: the monty script file
 *
 * Return: EXIT SUCCESS on succes, inverse otherwise
 */

int run_monty(FILE *script)
{
	stack_t *stack = NULL;
	char *line = NULL;
	size_t len = 0, exit_status = EXIT_SUCCESS;
	unsigned int line_number = 0, prev_tok_len = 0;
	void (*op_func)(stack_t**, unsigned int);

	if (init_stack(&stack) == EXIT_FAILURE)
		return (EXIT_FAILURE);

	while (getline(&line, &len, script) != -1)
	{
		line_number++;
		op_toks = strtow(line, DELIMS);
		if (op_toks == NULL)
		{
			if (is_empty_line(line, DELIMS))
				continue;
			free_s(&stack);
			return (malloc_error());
		}
		else if (op_toks[0][0] == '#')
		{
			free_toks();
			continue;
		}
		op_func = get_op_func(op_toks[0]);
		if (op_func == NULL)
		{
			free_s(&stack);
			exit_status = unknown_op_error(op_toks[0], line_number);
			free_toks();
			break;
		}
		prev_tok_len = token_arr_len();
		op_func(&stack, line_number);
		if (token_arr_len() != prev_tok_len)
		{
			if (op_toks && op_toks[prev_tok_len])
				exit_status = atoi(op_toks[prev_tok_len]);
			else
				exit_status = EXIT_FAILURE;
			free_toks();
			break;
		}
		free_toks();
	}
	free_s(&stack);

	if (line && *line == 0)
	{
		free(line);
		return (malloc_error());
	}

	free(line);
	return (exit_status);
}

/**
 * free_toks - free the token global var
 * Return: nothin;
 */

void free_toks(void)
{
	int i = 0;

	while (op_toks[i])
		free(op_toks[i]);
	free(op_toks);
}
