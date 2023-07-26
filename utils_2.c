#include "main.h"

/**
 * _putchar - ...
 * @c: ...
 */
void _putchar(char c)
{
	write(STDERR_FILENO, &c, 1);
}

/**
 * _putstr - ...
 * @s: ...
 */
void _putstr(char *s)
{
	int i;

	for (i = 0; s[i]; i++)
		write(STDERR_FILENO, &s[i], 1);
}

/**
 * _strlen - ...
 * @s: ...
 *
 * Return: length
 */
int _strlen(char *s)
{
	int i;

	for (i = 0; s[i]; i++)
		;
	return (i);
}

/**
 * _putnum - prints unsigned integer
 * @num: number
 *
 * Return: 0 on success, 1 on failure
 */
int _putnum(unsigned int num)
{
	unsigned int num_cp = num;
	char *num_str;
	int i, size = 0;

	if (num == 0)
	{
		_putchar('0');
		return (0);
	}

	while (num_cp)
	{
		size++;
		num_cp /= 10;
	}

	num_str = (char *)malloc(sizeof(char) * size);
	if (num_str == NULL)
	{
		return (1);
	}

	i = size - 1;
	while (num)
	{
		num_str[i] = '0' + (num % 10);
		num /= 10;
		i--;
	}

	i = 0;
	while (i < size)
	{
		_putchar(num_str[i]);
		i++;
	}
	free(num_str);
	return (0);
}

/**
 * print_stderr - ...
 * @argv: ...
 * @count: ...
 * @av: ...
 * @prompt: ...
 *
 * Return: 127 or -1
 */
int print_stderr(char *argv, unsigned int count, char *av, char *prompt)
{
	_putstr(argv);
	_putchar(':'), _putchar(' ');
	if (_putnum(count))
		return (-1);
	_putchar(':'), _putchar(' ');
	_putstr(av);
	_putchar(':'), _putchar(' ');
	_putstr(prompt), _putchar('\n');

	return (127);
}
