#include "shell.h"



/**
 * handle_input - check if the input is coming from the terminal,
 * if so print the prompt, then fetch the input from user through getline(),
 * check if EOF is reached
 *
 * @temp: buffer that will store the input
 * @len: length of the input
 */
void handle_input(char **temp, size_t *len)
{
	ssize_t input;

	if (isatty(STDIN_FILENO))
		printf("$ ");
	fflush(stdout);
	input = getline(temp, len, stdin);
	if (input == -1)
	{
		if (*temp)
			free(*temp);
		if (isatty(STDIN_FILENO))
			printf("\n");
		exit(0);
	}
	if ((*temp)[input - 1] == '\n')
		(*temp)[input - 1] = '\0';
	if (!strlen(*temp))
		return;
}

/**
 * execute_builtin - execute a builtin by calling check_builtin()
 *
 * @args: input that will be checked to see if it's a builtin command
 * @temp: buffer storing the input to be checked and possibly executed
 */
int execute_builtin(char **args, char *temp)
{
	int builtin;

	builtin = check_builtin(args, temp);
	if (builtin)
		return (1);
	return (0);
}

/**
 * child_process - if the input is a valid path command, create a new
 * child process and execute the program corresponding to the path.
 *
 * @args: tokenized input to be checked and executed
 * @temp: buffer containing the input
 * @argv: array containing outside arguments
 */
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
			fprintf(stderr, "%s: 1: %s", argv[0], strerror(errno));
			clean(temp, args);
			exit(1);
		}
	}
	else
	{
		wait(NULL);
	}
}


/**
 * main - contains the central loop of the shell, following these steps :
 * 1. reading input with handle_input() and checking if they come from TTY
 * 2. parsing input with tokenizer()
 * 3. execute commands through execute_builtin() if the command is a builtin
 * or through child_process() otherwise
 * 4. clean everything after execution
 *
 * @argc: number of line command arguments sent to the program from outside
 * @argv: array of line command arguments
 *
 * Return: 0 at the end of the loop
 */
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
			exit(0);
		}
		if (!execute_builtin(args, temp))
			child_process(args, temp, argv);
		clean(temp, args);
		temp = NULL;
		args = NULL;
	}
	return (0);
}
