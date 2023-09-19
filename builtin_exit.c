#include "main.h"

/**
 * builtin_exit - implements the built-in exit command
 * @av: the input
 * @argv: the arguments to the command
 * @err: errno
 * @count: line counter
 *
 * Return: 2 on failure of args
 */
int builtin_exit(char **av, char *argv, int err, int count)
{
	if (av[1])
	{
		if (not_a_number(av[1]))
		{
			errno = err = 2;
			print_stderr(argv, count, av[0], "Illegal number: ");
			_putstr(av[1]), _putchar('\n');
			return (2);
		}
		err = str_to_int(av[1]);
	}
	free_2d(av);
	exit(err);
}

/**
 * not_a_number - checks if the argument is a number
 * @s: the argument
 * Return: 1 or 0
 */
int not_a_number(char *s)
{
	int i;

	for (i = 0; s[i]; i++)
		if (s[i] < '0' || s[i] > '9')
			return (1);
	return (0);
}

/**
 * str_to_int - convert a string to int
 * @s: the string
 * Return: the int
 */
int str_to_int(char *s)
{
	int i, zero = 1, n = 0;

	for (i = 0; s[i]; i++)
		if (s[i] != '0')
		{
			zero = 0;
			break;
		}
	if (zero)
		return (0);
	for (i = 0; s[i]; i++)
	{
		n += (s[i] - '0');
		if (n != 0)
			n *= 10;
	}
	n /= 10;
	return (n);
}
