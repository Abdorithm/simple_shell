#include "main.h"

/**
 * readInput - ...
 *
 * Return: pointer to the input command
 */
char *readInput()
{
	char *line = NULL;
	size_t len = 0;
	int nread;

	nread = getline(&line, &len, stdin);

	if (nread == -1)
	{
		free(line);
		return (NULL);
	}
	/*
	 * printf("Retrieved line of length %d:\n", nread);
	 * fwrite(line, nread, 1, stdout);
	 */
	return (line);
}

/**
 * checkEmpty - ...
 * @buffer: the input
 *
 * Return: 1 if it is empty, meaning no commands
 * or arguments and only blank spaces, 0 otherwise
 */
int checkEmpty(char *buffer)
{
	int i;

	if (buffer[0] == '\0' || _strcmp(buffer, "\n") == 0)
		return (1);

	for (i = 0; buffer[i]; i++)
		if (buffer[i] != ' ' && buffer[i] != '\t' && buffer[i] != '\n')
			return (0);

	return (1);
}

/**
 * createChild - ...
 * @cmd: ...
 * @av: ...
 *
 * Return: ...
 */
int createChild(char *cmd, char **av)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Error");
		return (-1);
	}
	else if (child_pid == 0)
	{
		if (execve(cmd, av, __environ) == -1)
			perror(av[0]);
	}
	else if (child_pid > 0)
		wait(NULL);
	return (0);
}

/**
 * exec - execute the command
 * @cmd: the command
 * @av: the arguments, if any
 * @path: the environ PATH key
 * @argv: ...
 * @count: ...
 *
 * Return: 0 on success, -1 on failure
 */
int exec(char *cmd, char **av, char *path, char *argv, int count)
{
	char **path_dirs;
	char *path_found = NULL, *prompt;
	int executable = check_exec(cmd), isPATH = 0;

	path_dirs = get_dirs(path);
	if (path_dirs == NULL)
		return (-1);
	if (executable == 1)
	{
		if (createChild(cmd, av) == -1)
			return (-1);
	}
	else if (isPATH == 0)
	{
		/* returns the executable PATH, "x" if none, or NULL on failure */
		path_found = check_path(cmd, path_dirs);

		if (path_found != NULL && _strcmp(path_found, "x"))
		{
			isPATH = 1; /* there is an executable in PATH */
			if (createChild(path_found, av) == -1)
				return (-1);
		}
		else if (path_found == NULL) /* memory failure */
			return (-1);
	}
	if (isPATH == 0 && executable <= 0)
	{
		prompt = (executable == 0 ? "permission denied" : "not found");
		_putstr(argv);
		_putchar(':'), _putchar(' ');
		if (_putnum(count))
			return (-1);
		_putchar(':'), _putchar(' ');
		_putstr(av[0]);
		_putchar(':'), _putchar(' ');
		_putstr(prompt), _putchar('\n');
	}
	free(path_found), free_2d(path_dirs);
	return (0);
}

/**
 * main - Entry point
 * @argc: ...
 * @argv: ...
 *
 * Return: 0 on success, 1 on failure
 */
int main(int argc, char **argv)
{
	unsigned int count = 0;
	char *buffer = NULL, **av, *path;

	(void) argc;
	while (++count)
	{
		path = _getenv("PATH"); /* handling PATH */
		if (path == NULL)
			exit(EXIT_FAILURE);
		if (isatty(0)) /* checks for interactive & non-interactive modes */
			printf("($) ");

		buffer = readInput();
		if (buffer == NULL) /* EOF or input error */
			free(path), exit(EXIT_SUCCESS);
		if (checkEmpty(buffer))
		{
			free(path), free(buffer);
			continue;
		}
		av = get_args(buffer);
		free(buffer);
		if (av == NULL)
			exit(EXIT_FAILURE);

		if (_strcmp(av[0], "exit") == 0) /* handle exit */
			free(path), free_2d(av), exit(errno);
		if (_strcmp(av[0], "env") == 0) /* implement env built-in */
			print_env(__environ);
		else if (exec(av[0], av, path, argv[0], count) == -1)
			free_2d(av), free(path), exit(EXIT_FAILURE);
		free(path), free_2d(av);
	}
	return (0);
}
