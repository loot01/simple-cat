#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>

#define BUF_SIZE 4096

void	handle_stdin(char *buf)
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
		write(1, buf, num_bytes);
	}
}

void	handle_file(char *file_path, char *buf)
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
		write(1, buf, num_bytes);
	}
	close(fd);
}

int	main(int argc, char **argv)
{
	char	buf[BUF_SIZE];
	if (argc == 1)
	{
		handle_stdin(buf);
		return (0);
	}
	for (int i = 1; i < argc; i++)
	{
		if (strcmp(argv[i], "-") == 0)
			handle_stdin(buf);
		else
		{
			handle_file(argv[i], buf);
		}
	}
}
