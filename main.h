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
char *alloc_and_copy(char *src);
char **get_dirs(char *path);
void free_2d(char **array);
int check_exec(char *file);
char *string_concat(char *s1, char *s2);
char *check_path(char *file, char **dirs);

#endif
