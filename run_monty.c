#inclue "monty.h"

void free_toks(void);
void run_monty(FILE *script);

/**
 * run_monty - run the monty opcode
 * @stack: the stack to operate on
 *
 * Return: nothing
 */

void run_monty(FILE *script)
{
	stack_t *stack = NULL;
	unsigned int line_num = 0, i = 0;
	void (*op_func)(stack_t**, unsigned int);;
	char *line = NULL;
	size_t n = 0;

	while (getline(&line, &n, script) != -1)
	{
		line_num++;
		op_toks = tokenize(line, DELIM);
		if (op_toks == NULL)
		{
			/*free(stack);*/
			return;
		}

		else if (op_toks[0][0] == '#')
		{

			free_toks();
			continue;
		}
		op_func = get_opcode(op_toks[0]);
		if (op_func == NULL)
		{
			free_toks();
			/*free(stack);*/
		}

		op_func(&stack, line_num);
		free_toks();
	}
	/*free(stack);*/
	free(line);
	return;
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
