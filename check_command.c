#include "shell.h"
#include <stdio.h>
#include <string.h>
void free_tab(char **tab)
{
	int i = 0;

	for (; tab[i]; i++)
	{
		free(tab[i]);
	}
	free(tab);
}
int command_is_path(char *command)
{
	if (command[0] == '/')
		return (1);
	else
		return (0);
}
char *check_paths(char *command)
{
	char *path, *cp_path, **paths = NULL;
	char *check_path = NULL;
	int i = 0;

	path = getenv("PATH");
	cp_path = strdup(path);
	if (!path || !cp_path)
		return (NULL);
	paths = tokenizer(cp_path, ":");
	if (!paths)
		return (NULL);
	while(paths[i])
	{
		check_path = malloc(strlen(paths[i]) + strlen(command) + 2);
		if (!check_path)
		{
			free_tab(paths);
			return (NULL);
		}
		sprintf(check_path, "%s/%s", paths[i], command);
		if (access(check_path, X_OK) < 0)
		{
			free(check_path);
		}
		else
		{
			free_tab(paths);
			return(check_path);
		}
		i++;
	}
	free_tab(paths);
	return (NULL);
}
char *check_command(char *command)
{
	char *right_path;
	
	if (!command)
		return (NULL);
	if (command_is_path(command) == 1)
		return (command);
	else if ((right_path = check_paths(command)))
		return (right_path);
	else
		return (NULL);
}
