#include "main.h"

/**
 * _getenv - searches the environment list to find the environment variable key
 * @key: the environment variable
 *
 * Return: a pointer to the corresponding value string,
 * or NULL if there is no match
 */
char *_getenv(const char *key)
{
	char *value = NULL;
	int i = 0, j, k, equal, size;

	while (__environ[i])
	{
		equal = 1;
		for (j = 0; __environ[i][j] != '=' && key[j]; j++)
		{
			if (key[j] != __environ[i][j])
				equal = 0;
		}
		if (equal)
		{
			k = 0;
			for (size = j; __environ[i][size]; size++)
				;
			size -= j;
			j++;

			value = (char *)malloc(sizeof(char) * (size + 1));
			if (value == NULL)
				exit(EXIT_FAILURE);
			for ( ; __environ[i][j]; j++)
				value[k] = __environ[i][j], k++;
			value[k] = '\0';
			break;
		}
		i++;
	}
	return (value);
}

/**
 * get_args - construct an argument array similiar to argv
 * {"program_name", "arg1", "arg2", ..., NULL}
 * @buffer: user input
 *
 * Return: a null-terminated array of strings on success,
 * NULL on failure
 */
char **get_args(char *buffer)
{
	char **args = NULL, *token, *tmp, *tmp_token;
	int size = 0, i;

	tmp = _strdup(buffer);
	if (tmp == NULL)
		return (NULL);
	tmp_token = strtok(tmp, " \t\n");
	while (tmp_token != NULL)
	{
		size++;
		tmp_token = strtok(NULL, " \t\n");
	}
	free(tmp), size++;
	args = (char **)malloc(sizeof(char *) * size);
	if (args == NULL)
		return (NULL);
	for (i = 0; i < size - 1; i++)
	{
		token = strtok((i ? NULL : buffer), " \t\n");
		args[i] = _strdup(token);
		if (args[i] == NULL)
		{
			for (i--; i >= 0; i--)
				free(args[i]);
			free(args);
			return (NULL);
		}
	}
	args[size - 1] = NULL;
	return (args);
}

/**
 * get_dirs - construct an array of PATH directories
 * @path: the path environ value
 *
 * Return: a null-terminated array of strings,
 * NULL on failure
 */
char **get_dirs(char *path)
{
	char **dirs = NULL, *token, *tmp, *tmp_token;
	int size = 0, i;

	tmp = _strdup(path);
	if (tmp == NULL)
		exit(EXIT_FAILURE);
	tmp_token  = strtok(tmp, ":");
	while (tmp_token != NULL)
	{
		tmp_token = strtok(NULL, ":");
		size++;
	}
	free(tmp), size++;
	dirs = (char **)malloc(sizeof(char *) * size);
	if (dirs == NULL)
		exit(EXIT_FAILURE);
	for (i = 0; i < size - 1; i++)
	{
		token = strtok((i ? NULL : path), ":");
		dirs[i] = _strdup(token);
		if (dirs[i] == NULL)
		{
			for (i--; i >= 0; i--)
				free(dirs[i]);
			free(dirs);
			exit(EXIT_FAILURE);
		}
	}
	dirs[size - 1] = NULL;
	return (dirs);
}

/**
 * free_2d - frees an array of strings form memory
 * @array: the array
 */
void free_2d(char **array)
{
	int i = 0;

	while (array[i])
		free(array[i]), i++;
	free(array);
}

/**
 * print_env - prints the environment
 * @env: a null terminated array of strings,
 * with the following format var=value
 */
void print_env(char **env)
{
	unsigned int i;

	i = 0;
	while (env[i] != NULL)
	{
		printf("%s\n", env[i]);
		i++;
	}
}
