#include "shell.h"

/**
 * _getenv - Search for a specific environnement variable
 * and returns it if found.
 *
 * @env_variable: environnement variable to be searched
 *
 * Return: The environnement variable if found in the environ
 * global variable, NULL otherwise.
 */
char *_getenv(char *env_variable)
{
	char *temp;
	char **cp_env = environ;
	int i = 0, j;

	while (cp_env[i])
	{
		j = 0;
		temp = malloc(sizeof(char) * BUF);
		while (cp_env[i][j] != '=')
		{
			temp[j] = cp_env[i][j];
			j++;
		}
		temp[j] = '\0';
		if (strcmp(temp, env_variable) == 0)
		{
			free(temp);
			return (cp_env[i]);
		}
		else
		{
			free(temp);
			temp = NULL;
		}
		i++;
	}
	return (NULL);
}

