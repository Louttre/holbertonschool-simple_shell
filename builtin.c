#include "shell.h"

int check_builtin(char **arg)
{
	bl_t array[] = {
		{"exit", exit_func},
		{"env", printenv_func},
		{NULL, NULL}
	};
	int i;

	for(i = 0; array[i].command; i++)
	{
		if (strcmp(array[i].command, *arg) == 0)
		{
			array[i].func(arg);
			return (1);
		}
	}
	return (0);
}
void exit_func(char **arg)
{
	free_tab(arg);
	exit(2);
}
void printenv_func(char **arg)
{
	char **cp_env = environ;
	(void)arg;
	
	for (; *cp_env; cp_env++)
	{
		printf("%s\n", *cp_env);
	}
}
