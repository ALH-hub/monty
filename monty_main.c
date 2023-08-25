#include "monty.h"

/**
 * main - execute the monty project
 * @argc: argument counter
 * @argv: string of arguments
 *
 * Return: positive int on success
 */

int main(int argc, char **argv)
{
	FILE *file;

	if (argc != 2)
	{
		fprintf(stderr, "USAGE: monty file\n");
		exit(EXIT_FAILURE);
	}

	file = fopen(argv[1], "r");
	if (file == NULL)
	{
		fprintf(stderr, "Error: Can't open file %s\n", argv[1]);
		exit(EXIT_FAILURE);
	}
	run_monty(file);

	fclose(file);
	return (EXIT_SUCCESS);
}
