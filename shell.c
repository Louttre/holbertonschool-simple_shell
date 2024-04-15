#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include "test.h"
#define BUF 1024
int main(int argc, char *argv[])
{
	size_t len = 0;
	char *temp, *args[BUF];
	ssize_t nread;
	/*char *envp[BUF];*/
	pid_t pid;

	/*
	 * env = getenv("PATH");
	 * envp = {env, NULL};
	 */
	(void)argc, (void)argv;
	while (1)
	{
		printf("$ ");
		fflush(stdout);
		nread = getline(&temp, &len, stdin);
		if (nread == -1)
			exit(1);
		if (temp[nread - 1] == '\n')
			temp[nread - 1] = '\0';
		if (!strlen(temp))
			continue;
		tokenizer(args, temp);
		pid = fork();
		if (pid == -1)
		{
			perror("./shell");
			exit(1);
		}
		else if (pid == 0)
		{
			if (execve(args[0], args, NULL) == -1)
			{
				perror("./shell");
				exit(1);
			}
		}
		else
			wait(NULL);
	}
}
