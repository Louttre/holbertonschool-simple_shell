#include "shell.h"

/**
 * **tokenizer - Parses an input string and transform it
 * into an array of tokens.
 *
 * @temp: buffer containing the string to be tokenized
 * @delim: deliminator between tokens to be removed during
 * tokenization
 *
 * Return: args[], an array filled with the input tokens
 */
char **tokenizer(char *temp, char *delim)
{
	int i = 0;
	char *tokenized;
	char **args;

	args = malloc(sizeof(char *) * MAX_TOK);
	if (!args || !temp || !delim)
		return (NULL);
	tokenized = strtok(temp, delim);
	while (tokenized)
	{
		args[i] = strdup(tokenized);
		if (args[i] == NULL)
		{
			free_tab(args);
			return (NULL);
		}
		tokenized = strtok(NULL, delim);
		i++;
	}
	args[i] = NULL;
	return (args);
}
