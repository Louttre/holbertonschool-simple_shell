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

typedef struct
{
	char *command;
	void (*func)(char **s, char *temp);
} bl_t;
char **tokenizer(char *, char *);
void free_tab(char **tab);
int command_is_path(char *command);
char *check_paths(char *command);
char *check_command(char *command);
void clean(char *, char **);
int check_builtin(char **arg, char *temp);
void exit_func(char **args, char *temp);
void printenv_func(char **arg, char *temp);

#endif
