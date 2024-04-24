#include "shell.h"

/**
 * command_is_path - check if the command uses an explicit path syntax
 * (/usr/bin/ls for example)
 *
 * @command: command to be checked
 *
 * Return: 1 if command uses an explicit path syntax, 0 otherwise
 */
int command_is_path(char *command)
{
	if (command[0] == '/')
		return (1);
	else
		return (0);
}

/**
 * check_paths - search the command inside the PATH, and if so return the
 * precise path of the command
 *
 * @command: command to be checked inside the PATH
 * @argv: array of arguments sent by main()
 *
 * Return: if the path of the command is checked, returns said path,
 * returns NULL otherwise
 */
char *check_paths(char *command, char **argv)
{
	char *path, *cp_path, **paths = NULL;
	char *check_path = NULL;
	int i = 0;

	path = _getenv("PATH");
	cp_path = strdup(path);
	if (!path || !cp_path)
		return (NULL);
	paths = tokenizer(cp_path, ":");
	if (!paths)
	{
		free(cp_path);
		return (NULL);
	}
	while (paths[i])
	{
		check_path = malloc(strlen(paths[i]) + strlen(command) + 2);
		if (!check_path)
		{
			clean(cp_path, paths);
			return (NULL);
		}
		sprintf(check_path, "%s/%s", paths[i], command);
		if (access(check_path, X_OK) < 0)
			free(check_path);
		else
		{
			clean(cp_path, paths);
			free(command);
			return (check_path);
		}
		i++;
	}
	fprintf(stderr, "%s: %d: %s: %s\n", argv[0], errno, command, "not found");
	clean(cp_path, paths);
	free(command);
	return (NULL);
}

/**
 * check_command - Checks if the command is either an explicit path, or if
 * the command executable can be found inside the PATH environnment variable
 *
 * @command: command to be checked
 * @argv: array containing the arguments sent by main()
 *
 * Return: command if the command is a valid explicit path, right_path if
 * the command has a valid executable found inside the PATH variable,
 * NULL otherwise
 */
char *check_command(char *command, char **argv)
{
	char *right_path;

	if (!command)
		return (NULL);
	if (command_is_path(command) == 1)
		return (command);
	right_path = check_paths(command, argv);
	if (right_path)
		return (right_path);
	return (NULL);
}

