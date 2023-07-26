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
	int status;

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
	{
		wait(&status);
		if (WIFEXITED(status))
			errno = WEXITSTATUS(status);
	}
	return (0);
}

/**
 * exec - execute the command
 * @cmd: the command
 * @av: the arguments, if any
 * @argv: ...
 * @count: ...
 *
 * Return: 0 on success, other values on failure
 */
int exec(char *cmd, char **av, char *argv, int count)
{
	char **path_dirs = NULL;
	char *path_found = NULL, *prompt, *path = _getenv("PATH"); /* handling PATH */
	int executable = check_exec(cmd), isPATH = 0, err = 0;

	if (executable == 1)
	{
		if (createChild(cmd, av) == -1)
			return (-1);
	}
	else if (isPATH == 0 && path != NULL)
	{
		path_dirs = get_dirs(path);
		/* returns the executable PATH, NULL otherwise */
		path_found = check_path(cmd, path_dirs);

		if (path_found != NULL)
		{
			isPATH = 1; /* there is an executable in PATH */
			if (createChild(path_found, av) == -1)
				return (-1);
		}
	}
	if (isPATH == 0 && executable <= 0)
	{
		prompt = (executable == 0 ? "permission denied" : "not found");
		err = print_stderr(argv, count, av[0], prompt);
	}
	if (path)
		free(path);
	if (path_found)
		free(path_found);
	if (path_dirs)
		free_2d(path_dirs);
	return (err);
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
	int exit_stat, err = 0;
	unsigned int count = 0;
	char *buffer = NULL, **av;

	errno = 0;
	(void) argc;
	while (++count)
	{
		if (isatty(0)) /* checks for interactive & non-interactive modes */
			printf("($) ");
		buffer = readInput();
		if (buffer == NULL) /* EOF or input error */
			exit(EXIT_SUCCESS);
		if (checkEmpty(buffer))
		{
			free(buffer);
			continue;
		}
		av = get_args(buffer);
		free(buffer);
		if (av == NULL)
			exit(EXIT_FAILURE);
		if (_strcmp(av[0], "exit") == 0) /* handle exit */
		{
			if (builtin_exit(av, err) == 2)
				print_stderr(argv[0], count, av[0], "Illegal number");
		}
		else if (_strcmp(av[0], "env") == 0) /* implement env built-in */
			print_env(__environ);
		else
		{
			exit_stat = exec(av[0], av, argv[0], count), err = errno;
			if (exit_stat == -1)
				free_2d(av), exit(EXIT_FAILURE);
			else if (exit_stat == 127 && !isatty(0))
				free_2d(av), exit(127);
		}
		free_2d(av);
	}
	return (0);
}
