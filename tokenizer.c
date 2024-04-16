#include "shell.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

char **tokenizer(char *temp, char *delim)
{
	int i = 0;
	char *tokenized;
	char **args;
	
	args = malloc(sizeof(char *) * MAX_TOK);
	if (!args || !temp || !delim)
		return (NULL);	
	tokenized = strtok(temp, delim);
	while(tokenized)
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
