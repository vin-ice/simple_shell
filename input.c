#define _POSIX_C_SOURCE 2
#include <stdio.h>
#include <string.h>

#include "common.h"
#include "input.h"
#include "mem.h"
#include "_string.h"

#define READ_BUFFER_SIZE 4096

/**
 * _getline - reads a line from stream and loads to buffer
 * @lineptr: Holds characters read from stream
 * @n: Length of characters to read
 * @stream: source to read from
 *
 * Return: characters read from stream
 */
ssize_t _getline(char **lineptr, size_t *n, FILE *stream)
{
	int fd = -1, i = 0;
	size_t len = 0;
	ssize_t n_read = 0;
	static char buff[READ_BUFFER_SIZE] = {0};
	static ssize_t buff_count, buff_cursor;
	char *line = *lineptr;

	if (lineptr == NULL || stream == NULL)
		return (-1);

	fd = fileno(stream);
	if (fd < 0)
	{
		errno = EBADF;
		return (-1);
	}

	while (1)
	{
		if (buff_cursor >= buff_count)
		{
			buff_count = read(fd, buff, READ_BUFFER_SIZE);
			buff_cursor = 0;
			if (buff_count == 0)
			{
				break;
			} else if (buff_count == -1)
			{
				perror("_getline: read");
				return (-1);
			}
		}

		for (i = buff_cursor; i < buff_count && buff[i] != '\n'; i++)
			;

		if (i < buff_count)
		{
			len = i - buff_cursor + 1;
			line = (char *) realloc(line, n_read + len + 2);
			if (line == NULL)
			{
				perror("_getline: realloc");
				return (-1);
			}
			memcpy(line + n_read, buff + buff_cursor, len);
			n_read += len;
			buff_cursor = i + 1;
			break;
		}
		len = buff_count - buff_cursor;
		line = (char *) realloc(line, n_read + len + 2);
		if (line == NULL)
		{
			perror("_getline: realloc");
			return (-1);
		}
		memcpy(line + n_read, buff + buff_cursor, len);
		n_read += len;
		buff_cursor = buff_count;
	}
	line[n_read] = '\0';
	*lineptr = line;
	*n = n_read;
	return (n_read);
}

/**
 * read_file - Reads content of a file
 * @pathname: path to file
 * Return: Pointer to memory with data;
 */
char *read_file(char *pathname)
{
	size_t n_read = 0, size;
	FILE *fp;
	char *buffer = NULL;

	fp = fopen(pathname, "rb");
	if (fp == NULL)
	{
		perror("fopen");
		goto _end;
	}

	if (fseek(fp, 0L, SEEK_END) == -1)
	{
		perror("fseek");
		goto _end;
	}
	size = ftell(fp);
	rewind(fp);

	if (size > 0)
	{
		buffer = malloc(size + 1);
		if (buffer == NULL)
		{
			perror("malloc");
			goto _end;
		}

		memset(buffer, '\0', (size + 1));
		n_read = fread(buffer, sizeof(buffer), sizeof(*buffer), fp);
		if (n_read != sizeof(*buffer))
		{
			fprintf(stderr, "fread() failed: %lu\n", n_read);
			goto _end;
		}
	}
_end:
	fclose(fp);
	return (buffer);
}

