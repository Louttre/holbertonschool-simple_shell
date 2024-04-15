#include "test.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#define BUF 1024
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
