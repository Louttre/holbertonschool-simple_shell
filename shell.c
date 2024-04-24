#include "shell.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>

void handle_input(char **temp, size_t *len);
void execute_builtin(char **args, char *temp);
void child_process(char **args, char *temp, char **argv);

int main(int argc, char *argv[])
{
	size_t len = 0;
	char *temp = NULL, **args = NULL;

	(void)argc, (void)argv;
	while (1)
	{
		handle_input(&temp, &len);
		args = tokenizer(temp, " ");
		if (!args)
		{
			free(temp);
			exit(1);
		}
		execute_builtin(args, temp);
		child_process(args, temp, argv);
		clean(temp, args);
		temp = NULL;
		args = NULL;
	}
	return 0;
}

void handle_input(char **temp, size_t *len)
{
	ssize_t input;

	if (isatty(STDIN_FILENO))
		printf("$ ");
	fflush(stdout);
	input = getline(temp, len, stdin);
	if (input == -1 || feof(stdin))
	{
		if (*temp)
			free(*temp);
		if (isatty(STDIN_FILENO))
			printf("\n");
		exit(1);
	}
	if ((*temp)[input - 1] == '\n')
		(*temp)[input - 1] = '\0';
	if (!strlen(*temp))
		return;
}

void execute_builtin(char **args, char *temp)
{
	int builtin;

	builtin = check_builtin(args, temp);
	if (builtin)
		return;
}

void child_process(char **args, char *temp, char **argv)
{
	pid_t pid;

	args[0] = check_command(args[0], argv);
	if (!args[0])
		return;
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
			fprintf(stderr, "%s: %d: %s", argv[0], errno, strerror(errno));
			clean(temp, args);
			exit(1);
		}
	}
	else
	{
		wait(NULL);
	}
}

void clean(char *temp, char **args)
{
	free(temp);
	free_tab(args);
}

