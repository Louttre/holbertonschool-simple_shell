#include "shell.h"

int check_builtin(char **arg, char *temp)
{
	bl_t array[] = {
		{"exit", exit_func},
		{"env", printenv_func},
		{"printenv", printenv_func},
		{NULL, NULL}
	};
	int i;

	for(i = 0; array[i].command; i++)
	{
		if (strcmp(array[i].command, *arg) == 0)
		{
			array[i].func(arg, temp);
			return (1);
		}
	}
	return (0);
}
void exit_func(char **arg, char *temp)
{
	clean(temp, arg);
	exit(1);
}
void printenv_func(char **arg, char *temp)
{
	char **cp_env = environ;
	(void)arg, (void)temp;
	
	for (; *cp_env; cp_env++)
	{
		printf("%s\n", *cp_env);
	}
}
