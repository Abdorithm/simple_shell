#ifndef _MAIN_H_
#define _MAIN_H_

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/wait.h>
#include <stdint.h>

char *_getenv(const char *key);
char **get_args(char *buffer);
char **get_dirs(char *path);
void free_2d(char **array);
int check_exec(char *file);
char *string_concat(char *s1, char *s2);
char *check_path(char *file, char **dirs);
char *_strdup(char *str);
int _strcmp(char *x, char *y);
void print_env(char **env);
void _putchar(char c);
void _putstr(char *s);
int _strlen(char *s);
int _putnum(unsigned int num);
int print_stderr(char *argv, unsigned int count, char *av, char *prompt);
int builtin_exit(char **av, char *argv, int err, int count);
int not_a_number(char *s);
int str_to_int(char *s);

#endif
