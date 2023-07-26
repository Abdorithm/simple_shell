#include "main.h"

/**
 * check_exec - ...
 * @file: ...
 *
 * Return: 1 if file exists and is executable,
 * 0 if file exists but not executable (no permission),
 * -1 if file does not exist
 */
int check_exec(char *file)
{
	struct stat sb;
	int slash = 0, i = 0;

	while (file[i])
	{
		if (file[i] == '/')
		{
			slash = 1;
			break;
		}
		i++;
	}
	if (stat(file, &sb) == 0 && sb.st_mode & S_IXUSR && slash)
		return (1);
	else if (stat(file, &sb) == 0 && slash)
		return (0);
	return (-1);
}

/**
 * check_path - ...
 * @file: ...
 * @dirs: ...
 *
 * Return: the path of the executable if found
 * NULL otherwise
 */
char *check_path(char *file, char **dirs)
{
	struct stat sb;
	int i = 0;
	char *concat, *concat_path;

	concat = string_concat("/", file);
	if (concat == NULL)
	{
		exit(EXIT_FAILURE);
	}
	for (i = 0; dirs[i]; i++)
	{
		concat_path = string_concat(dirs[i], concat);
		if (concat_path == NULL)
		{
			free(concat);
			exit(EXIT_FAILURE);
		}
		if (stat(concat_path, &sb) == 0 && sb.st_mode & S_IXUSR)
		{
			free(concat);
			return (concat_path);
		}
		free(concat_path);
	}
	free(concat);
	return (NULL); /* no path was found */
}

/**
 * string_concat - a function that concatenates two strings.
 *
 * @s1: first string
 * @s2: second string
 *
 * Return: final string, NULL on failure
 */
char *string_concat(char *s1, char *s2)
{
	int i, j, k;
	char *s;

	for (i = 0; s1[i]; i++)
		;
	for (j = 0; s2[j]; j++)
		;
	s = (char *)malloc(sizeof(char) * (i + j + 1));
	if (s == NULL)
		return (NULL);
	for (k = 0; k < i; k++)
		s[k] = s1[k];
	for (k = 0; k < j; k++)
		s[k + i] = s2[k];
	s[i + j] = '\0';
	return (s);
}

/**
 * _strdup - returns a pointer to a newly allocated space in memory,
 * which contains a copy of the string given as a parameter.
 * @str: the source string
 *
 * Return: returns a pointer to the duplicated string.
 * It returns NULL if insufficient memory was available
 */
char *_strdup(char *str)
{
	char *copy;
	int i, size = 0;

	if (str == NULL)
		return (NULL);

	while (str[size] != '\0')
		size++;

	copy = (char *)malloc((sizeof(char) * size) + 1);
	if (copy == NULL)
		return (NULL);

	for (i = 0; i < size; i++)
		copy[i] = str[i];
	copy[size] = '\0';

	return (copy);
}

/**
 * _strcmp - compares 2 strings
 * @x: ...
 * @y: ...
 *
 * Return: 0 or 1
 */
int _strcmp(char *x, char *y)
{
	int i, j;

	for (i = 0; x[i]; i++)
		;
	for (j = 0; y[j]; j++)
		;
	if (i != j)
		return (1);

	for (i = 0; x[i]; i++)
		if (x[i] != y[i])
			return (1);
	return (0);
}
