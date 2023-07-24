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
	int nread, i;

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
	for (i = 0; line[i] != '\0'; i++)
		;
	line[i - 1] = '\0';
	return (line);
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
		{
			perror(av[0]);
		}
	}
	else if (child_pid > 0)
	{
		wait(NULL);
	}
	return (0);
}

/**
 * exec - execute the command
 * @cmd: the command
 * @av: the arguments, if any
 * @path: the environ PATH key
 *
 * Return: 0 on success, 1 on failure
 */
int exec(char *cmd, char **av, char *path)
{
	char **path_dirs = get_dirs(path);
	char *path_found;
	int executable = check_exec(cmd), isPATH = 0;

	/* printf("processing\n"); */
	if (executable)
	{
		printf("\texe\n");
		createChild(cmd, av);
	}
	else if (!isPATH)
	{
		path_found = check_path(cmd, path_dirs);
		if (path_found != NULL)
		{
			/* printf("\tPATH\n"); */
			createChild(path_found, av);
		}
	}
	else
		printf("%s: not found\n", av[0]);
	/* printf("ending\n"); */
	free(path_found);
	free_2d(path_dirs);
	return (0);
}

/**
 * main - Entry point
 *
 * Return: 0 on success, 1 on failure
 */
int main(void)
{
	int execShell = 1;
	char *buffer = NULL;
	char **av;
	/* handling PATH */
	char *path = _getenv("PATH");

	while (execShell)
	{
		/* checks for interactive & non-interactive modes */
		if (isatty(0))
			printf("($) ");

		buffer = readInput();
		if (buffer == NULL)
		{
			free(path);
			break;
		}
		if (buffer[0] == '\0' || strcmp(buffer, "\n") == 0)
		{
			free(buffer);
			continue;
		}
		av = get_args(buffer);
		free(buffer);
		if (strcmp(av[0], "exit") == 0)
		{
			free(path);
			free_2d(av);
			break;
		}
		if (exec(av[0], av, path) == 1)
		{
			free_2d(av);
			exit(EXIT_FAILURE);
		}

		free_2d(av);
	}
	return (0);
}
