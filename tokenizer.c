#include "shell.h"

char **tokenizer(char *args[], char *temp)
{
	int i = 0;
	char *tokenized;

	tokenized = strtok(temp," ");
	while(tokenized)
	{
		args[i] = tokenized;
		tokenized = strtok(NULL," ");
		i++;
	}
	args[i] = NULL;
	return (args);
}
