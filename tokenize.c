#include "monty.h"

/**
 * tokenize - tokenize a given line of strings
 * @line: the string to tokenize
 *
 * Return: the pointer to the tokenized strings
 */

char **tokenize(char *line)
{
	if (line == NULL)
		return (NULL);

	int len = strlen(line), i = 0;
	char **words = malloc((len + 1) * sizeof(char *));
	char *word;

	word = strtok(line, DELIM);
	while (word != NULL)
	{
		int lenw = strlen(word);

		words[i] = malloc((lenw + 1) * sizeof(char *));
		if (words[i] == NULL)
		{
			while (i >= 0)
			{
				free(words[i]);
				i--;
			}
			return (NULL);
		}

		strcpy(words[i], word);

		word = strtok(NULL, DELIM);
		i++;
	}
	words[i] = NULL;

	return (words);
}
