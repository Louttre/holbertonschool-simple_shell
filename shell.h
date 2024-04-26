#ifndef SHELL_H
#define SHELL_H


/* LIBRARIES */
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

/* MACROS & GLOBAL*/
#define BUF 2048
#define MAX_TOK 100
extern char **environ;

/* STRUCTURES */

/**
 * struct builtin_struct - used to define builtins
 *
 * @command: command associated to the builtin (exit, env...)
 * @func: function associated to the builtin
 */
typedef struct builtin_struct
{
        char *command;
        void (*func)(char **s, char *temp);
} bl_t;


/* PROTOTYPES */
/*---shell.c---*/
int child_process(char **args, char *temp, char **argv);
int execute_builtin(char **args, char *temp);
void handle_input(char **temp, size_t *len);

/*---_getenv.c---*/
char *_getenv(char *env_variable);

/*---builtin.c---*/
int check_builtin(char **arg, char *temp);
void exit_func(char **args, char *temp);
void printenv_func(char **arg, char *temp);

/*---check_command.c---*/
char *check_command(char *command, char **argv);
char *check_paths(char *command, char **argv);
int command_is_path(char *command);
int path_finding(char *command);

/*---memory_handler.c---*/
void clean(char *, char **);
void free_tab(char **tab);

/*---tokenizer.c---*/
char **tokenizer(char *, char *);

#endif
