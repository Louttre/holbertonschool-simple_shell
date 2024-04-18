#ifndef TES_H
#define TES_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#define BUF 1024
#define MAX_TOK 100

extern char **environ;

struct builtin
{
	char *builtin_command;
	void (*func)(char **s);
};
typedef builtin bl_t;
char **tokenizer(char *, char *);
void free_tab(char **tab);
int command_is_path(char *command);
char *check_paths(char *command);
char *check_command(char *command);
void clean(char *, char **);
void check_builtin(char **arg);
void exit_func(**args);
void printenv_func(char **arg);

#endif
