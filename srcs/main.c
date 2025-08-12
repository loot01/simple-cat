#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#define BUF_SIZE 4096
#define FLAG_COUNT 7

void	print_w_flags(int *flags, char *buf, int num_bytes)
{
	int	i;
	int	j;
	int	line_num;
	int	is_non_printable;
	int	is_newline;
	int	digits_num;

	i = 0;
	digits_num = 0;
	line_num = 1;
	is_newline = 1;
	while (i < num_bytes)
	{
		if (is_newline == 1 && flags[2] == 1)
		{
			j = 0;
			digits_num = ft_get_digits(line_num);
			while (j++ < 6 - digits_num)
				write(1, " ", 1);
			ft_putnbr(line_num);
			write(1, "  ", 2);
			is_newline = 0;
		}
		is_non_printable = buf[i] < 20 || buf[i] > 126;
		if (buf[i] == '\t' && flags[4] == 1)
		{
			write(1, "^I", 2);
			i++;
			continue ;
		}
		if (is_non_printable == 1 && flags[5] == 1)
		{
			write(1, ".", 1);
			i++;
			continue ;
		}
		if (buf[i] == '\n')
		{
			if (flags[1] == 1)
				write(1, "$", 1);
			line_num++;
			is_newline = 1;
		}
		write(1, &buf[i], 1);
		i++;
	}
}

void	handle_stdin(char *buf, int *flags)
{
	int	fd;
	int	num_bytes;

	fd = 0;
	num_bytes = 1;
	while (num_bytes != 0)
	{
		num_bytes = read(fd, buf, BUF_SIZE);
		if (num_bytes < 0)
		{
			printf("simple-cat: Error reading from stdin\n");
			return ;
		}
		print_w_flags(flags, buf, num_bytes);
	}
}

void	handle_file(char *file_path, char *buf, int *flags)
{
	int	fd;
	int	num_bytes;

	fd = open(file_path, O_RDONLY);
	num_bytes = 1;
	if (fd == -1)
	{
		printf("simple-cat: Error opening <%s>\n", file_path);
		return ;
	}
	while (num_bytes != 0)
	{
		num_bytes = read(fd, buf, BUF_SIZE);
		if (num_bytes < 0)
		{
			printf("simple-cat: Error reading from %s\n", file_path);
			return ;
		}
		print_w_flags(flags, buf, num_bytes);
	}
	close(fd);
}

int	handle_flags(char *str, int *flags)
{
	int	is_flag;
	
	is_flag = 0;
	if (strcmp(str, "-b") == 0)
		flags[0] = is_flag = 1;
	if (strcmp(str, "-E") == 0)
		flags[1] = is_flag = 1;
	if (strcmp(str, "-n") == 0)
		flags[2] = is_flag = 1;
	if (strcmp(str, "-s") == 0)
		flags[3] = is_flag = 1;
	if (strcmp(str, "-T") == 0)
		flags[4] = is_flag = 1;
	if (strcmp(str, "-V") == 0)
		flags[5] = is_flag = 1;
	return (is_flag);
}

int	main(int argc, char **argv)
{
	char	buf[BUF_SIZE];
	int	flags[FLAG_COUNT];
	/*
	 flags' values:
		0: -b number nonempty output lines (NOT IMPLEMENTED)
		1: -E display $ at end of each line
		2: -n number all output lines
		3: -s suppress repeated empty output lines (NOT IMPLEMENTED)
		4: -T display TAB characters as ^I
		5: -V show non printable characters as .
	*/

	for (int i = 0; i < FLAG_COUNT; i++)
		flags[i] = 0;
	if (argc == 1)
	{
		handle_stdin(buf, flags);
		return (0);
	}
	for (int i = 1; i < argc; i++)
		handle_flags(argv[i], flags);
	for (int i = 1; i < argc; i++)
	{
		if (argv[i][0] == '-')
			continue ;
		if (strcmp(argv[i], "-") == 0)
			handle_stdin(buf, flags);
		else
		{
			handle_file(argv[i], buf, flags);
		}
	}
}
