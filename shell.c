#include "shell.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>
void clean(char *a, char **b)
{
	free(a);
	free_tab(b);
}
int main(int argc, char *argv[])
{
	size_t len = 0;
	char *temp = NULL, **args = NULL;
	ssize_t input;
	pid_t pid;
	int loop = 1, builtin;

	(void)argc, (void)argv;
	while (loop)
	{
		if (isatty(STDIN_FILENO))
			printf("$ ");
		fflush(stdout);
		input = getline(&temp, &len, stdin);
		if (input == -1 || feof(stdin))
		{
			if (temp)
				free(temp);
			if (isatty(STDIN_FILENO))
				printf("\n");
			exit(1);
		}
		if (temp[input - 1] == '\n')
			temp[input - 1] = '\0';
		if (!strlen(temp))
			continue;
		args = tokenizer(temp, " ");
		if (!args)
		{
			free(temp);
			exit(1);
		}
		builtin = check_builtin(args, temp);
		if (builtin)
		{
			clean(temp, args);
			temp = NULL;
			args = NULL;
			continue;
		}
		args[0] = check_command(args[0]);
		if (!args[0])
		{
			clean(temp, args);
			args = NULL;
			temp = NULL;
			continue;
		}
		pid = fork();
		if (pid == -1)
		{
			perror("fork");
			clean(temp, args);
			exit(1);
		}
		else if (pid == 0)
		{
			if (execve(args[0], args, NULL) == -1)
			{
				perror("execve");
				clean(temp, args);
				exit(1);
			}
		}
		else
		{
			wait(NULL);
			free_tab(args);
		}
	}
	free(temp);
	return (0);
}
