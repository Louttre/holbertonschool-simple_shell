#include "shell.h"

/**
 * check_builtin - checks if an input is a builtin command and if so
 * executes the builtin
 *
 * @arg: the command to be checked and executed if it's a builtin command
 * @temp: buffer containing the command
 *
 * Return: 1 if no builtin command is found or if the builtin command is
 * successfully executed, 0 otherwise
 */
int check_builtin(char **arg, char *temp)
{
	bl_t array[] = {
		{"exit", exit_func},
		{"env", printenv_func},
		{"printenv", printenv_func},
		{NULL, NULL}
	};
	int i;

	if (!*arg)
		return (1);
	for (i = 0; array[i].command; i++)
	{
		if (strcmp(array[i].command, *arg) == 0)
		{
			array[i].func(arg, temp);
			return (1);
		}
	}
	return (0);
}

/**
 * exit_func - builtin command exiting the shell after cleaning the memory
 *
 * @arg: arguments to be cleaned before exit
 * @temp: buffer to be cleaned before exit
 */
void exit_func(char **arg, char *temp)
{
	clean(temp, arg);
	exit(0);
}


/**
 * printenv_func - builtin command printing the current
 * environnement of the process
 *
 * @arg : not used
 * @temp : not used
 */
void printenv_func(char **arg, char *temp)
{
	char **cp_env = environ;
	(void)arg, (void)temp;

	for (; *cp_env; cp_env++)
	{
		printf("%s\n", *cp_env);
	}
}

