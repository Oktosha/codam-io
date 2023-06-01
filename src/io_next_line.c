/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   io_next_line.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: dkolodze <dkolodze@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/26 21:21:12 by dkolodze      #+#    #+#                 */
/*   Updated: 2023/06/01 15:43:24 by dkolodze      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>

#include "codam_io.h"

static int	newline_position(char *line, int length)
{
	int	i;

	i = 0;
	while (i < length)
	{
		if (line[i] == '\n')
			return (i);
		i += 1;
	}
	return (-2);
}

static void	memory_copy(char *dst, char *src, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		dst[i] = src[i];
		i += 1;
	}
}

static int	extract_from_buffer_till_newline_or_end(char **str, t_io_buffer *b)
{
	int		old_len;
	int		added_len;
	char	*new_str;

	if (b->len == 0)
		return (0);
	added_len = newline_position(b->data + b->start, b->len) + 1;
	if (added_len == -1)
		added_len = b->len;
	old_len = 0;
	if (*str != NULL)
		old_len = io_signed_strlen(*str);
	new_str = io_wrapped_malloc((old_len + added_len + 1) * sizeof(char));
	if (new_str == NULL)
		return (-1);
	memory_copy(new_str, *str, old_len);
	memory_copy(new_str + old_len, b->data + b->start, added_len);
	new_str[old_len + added_len] = '\0';
	free(*str);
	*str = new_str;
	b->start += added_len;
	b->len -= added_len;
	if (b->len == 0)
		b->start = 0;
	return (0);
}

static t_io_next_line_status	clean_up_error( \
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
	*line = NULL;
	if (extract_from_buffer_till_newline_or_end(line, &(file->buffer)))
		return (clean_up_error(IO_NEXT_LINE_MEMORY_ERROR, file, line));
	while (!*line || newline_position(*line, io_signed_strlen(*line)) == -2)
	{
		file->buffer.len = read(file->fd, file->buffer.data, IO_BUFFER_SIZE);
		if (file->buffer.len < 0)
			return (clean_up_error(IO_NEXT_LINE_READ_ERROR, file, line));
		if (file->buffer.len == 0)
			break ;
		if (extract_from_buffer_till_newline_or_end(line, &(file->buffer)))
			return (clean_up_error(IO_NEXT_LINE_MEMORY_ERROR, file, line));
	}
	if (*line == NULL)
		return (IO_NEXT_LINE_EOF);
	return (IO_NEXT_LINE_SUCCESS);
}
