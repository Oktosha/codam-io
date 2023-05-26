/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   io_next_line.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: dkolodze <dkolodze@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/26 21:21:12 by dkolodze      #+#    #+#                 */
/*   Updated: 2023/05/26 22:12:58 by dkolodze      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

#include "codam_io.h"
#include "codam_io_impl.h"

static int	contains_newline(char *line)
{
	int i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '\n')
			return (1);
		i += 1;
	}
	return (0);
}

static int	append(char **dst, char *src, int length)
{

}

static int read_into_buffer(t_io_input_file *file)
{

}

static t_io_next_line_status clean_up_error( \
	t_io_next_line_status err, \
	t_io_input_file *file, \
	char **line)
{
	file->fd = -1;
	io_reset_buffer(&(file->buffer));
	free(*line);
	*line = NULL;
	if (err == IO_NEXT_LINE_MEMORY_ERROR)
		return (IO_NEXT_LINE_MEMORY_ERROR);
	if (err == IO_NEXT_LINE_READ_ERROR)
	{
		if (IO_FAILFAST_ON_READ_ERROR)
			exit(IO_EXIT_READ_ERROR);
		return (IO_NEXT_LINE_READ_ERROR);
	}
	io_err("io_nex_line::clean_up_error called with uknown err = %d\n", err);
	exit(IO_EXIT_WRONG_ARGS_ERROR);
}

t_io_next_line_status	io_next_line(t_io_input_file *file, char **line)
{
	int			retcode;
	t_io_buffer	*buffer;

	*line = NULL;
	buffer = &(file->buffer);
	if (append(line, buffer->data + buffer->start, buffer->len))
		return (clean_up_error(IO_NEXT_LINE_MEMORY_ERROR, file, line));
	while (!contains_newline(line))
	{
		retcode = read_into_buffer(file);
		if (retcode == IO_NEXT_LINE_READ_ERROR)
			return (clean_up_error(IO_NEXT_LINE_READ_ERROR, file, line));
		if (append(line, buffer->data + buffer->start, buffer->len))
			return (clean_up_error(IO_NEXT_LINE_MEMORY_ERROR, file, line));
		if (retcode == IO_NEXT_LINE_EOF)
			break ;
	}
	
}