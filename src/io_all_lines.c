/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   io_all_lines.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: dkolodze <dkolodze@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/29 19:12:45 by dkolodze      #+#    #+#                 */
/*   Updated: 2023/06/01 14:08:14 by dkolodze      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "codam_io.h"

static int s_adapt_next_line_status(int status)
{
	if (status == IO_NEXT_LINE_MEMORY_ERROR)
		return (IO_ALL_LINES_MEMORY_ERROR);
	if (status == IO_NEXT_LINE_READ_ERROR)
		return (IO_ALL_LINES_READ_ERROR);
	if (status == IO_NEXT_LINE_EOF)
		return (IO_ALL_LINES_SUCCESS);
	if (status == IO_NEXT_LINE_SUCCESS)
	{
		io_err("unexpected adapt_next_line_status(IO_NEXT_LINE_SUCCESS)\n");
		io_err("adapt_next_line_status should be called after EOF or on err\n");
		exit(IO_EXIT_WRONG_ARGS_ERROR);
	}
	io_err("unexpected call adapt_next_line_status(%d)\n", status);
	io_err("no such status can be returned from io_next_line\n");
	exit(IO_EXIT_WRONG_ARGS_ERROR);
}

static int s_increase_capacity(char ***lines, int *capacity)
{
	int		new_capacity;
	char	**new_lines;
	int		i;

	new_capacity = *capacity * 2;
	if (new_capacity < 4)
		new_capacity = 4;
	new_lines = io_wrapped_malloc(new_capacity * sizeof(char *));
	if (new_lines == NULL)
		return (-1);
	io_memset(new_lines, new_capacity * sizeof(char *), 0);
	i = 0;
	while (i < *capacity)
	{
		new_lines[i] = (*lines)[i];
		i += 1;
	}
	free(*lines);
	*lines = new_lines;
	*capacity = new_capacity;
	return (0);
}

static t_io_all_lines_status s_cleanup( \
	char ***lines, \
	int line_cnt, \
	t_io_input_file *file, \
	t_io_all_lines_status status)
{
	int i;
	int close_status;

	if (status == IO_ALL_LINES_OPEN_ERROR)
		return (IO_ALL_LINES_OPEN_ERROR);
	close_status = io_close(file);
	if (close_status != IO_CLOSE_SUCCESS && status == IO_ALL_LINES_SUCCESS)
		status = IO_ALL_LINES_CLOSE_ERROR;
	if (status != IO_ALL_LINES_SUCCESS)
	{
		i = 0;
		while (i < line_cnt)
			free((*lines)[i++]);
		free(*lines);
		*lines = NULL;
	}
	return (status);
}

t_io_all_lines_status	io_all_lines(char *filename, char ***lines)
{
	t_io_input_file file;
	int				status;
	int				capacity;
	int				cnt;

	*lines = NULL;
	capacity = 0;
	cnt = -1;
	if (io_open_for_read(filename, &file) != IO_OPEN_FOR_READ_SUCCESS)
		return (s_cleanup(lines, 0, &file, IO_ALL_LINES_OPEN_ERROR));
	status = IO_NEXT_LINE_SUCCESS;
	while (status == IO_NEXT_LINE_SUCCESS)
	{
		cnt += 1;
		if (cnt == capacity && s_increase_capacity(lines, &capacity) == -1)
			return (s_cleanup(lines, cnt, &file, IO_ALL_LINES_MEMORY_ERROR));
		status = io_next_line(&file, &((*lines)[cnt]));
	}
	return s_cleanup(lines, cnt, &file, s_adapt_next_line_status(status));
}
