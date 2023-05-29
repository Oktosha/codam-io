/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   io_all_lines.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: dkolodze <dkolodze@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/29 19:12:45 by dkolodze      #+#    #+#                 */
/*   Updated: 2023/05/29 20:01:07 by dkolodze      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "codam_io.h"

static int free_read(char ***lines, int line_count)
{
	int i;

	i = 0;
	while (i < line_count)
	{
		free((*lines)[i]);
		i += 1;
	}
	free(*lines);
	*lines = NULL;
	return (0);
}

static int adapt_nl_err(t_io_next_line_status status)
{
	if (status == IO_NEXT_LINE_MEMORY_ERROR)
		return (IO_ALL_LINES_MEMORY_ERROR);
	if (status == IO_NEXT_LINE_READ_ERROR)
		return (IO_NEXT_LINE_READ_ERROR);
	io_err("Unexpected error status %d ", status);
	io_err("returned from io_next_line to io_all_lines\n");
	exit(IO_EXIT_WRONG_ARGS_ERROR);
}

static int adapt_close_status(t_io_close_status status)
{
	if (status == IO_CLOSE_ERROR)
		return (IO_ALL_LINES_CLOSE_ERROR);
	if (status == IO_CLOSE_SUCCESS)
		return (IO_ALL_LINES_SUCCESS);
	io_err("Unexpected close status %d ", status);
	io_err("returned from io_close to io_all_lines\n");
	exit(IO_EXIT_WRONG_ARGS_ERROR);
}

static int increase_capacity(char ***lines, int line_count, int *capacity)
{

}

t_io_all_lines_status	io_all_lines(char *filename, char ***lines)
{
	t_io_input_file file;
	int				status;
	int				capacity;
	int				cnt;

	if (io_open_for_read(filename, &file) != IO_OPEN_FOR_READ_SUCCESS)
		return (IO_ALL_LINES_OPEN_ERROR);
	capacity = 3;
	*lines = io_wrapped_malloc(capacity * sizeof(char *));
	if (*lines == NULL)
		return (io_close(&file), IO_ALL_LINES_MEMORY_ERROR);
	io_memset(*lines, capacity * sizeof(char *), 0);
	cnt = 0;
	status = io_next_line(&file, &((*lines)[cnt]));
	while (status == IO_NEXT_LINE_SUCCESS)
	{
		cnt += 1;
		if (cnt == capacity && increase_capacity(lines, cnt, &capacity) == -1)
			return (io_close(&file), IO_ALL_LINES_MEMORY_ERROR);
		status = io_next_line(&file, &((*lines)[cnt]));
	}
	if (status != IO_NEXT_LINE_EOF)
		return (io_close(&file), free_read(lines, cnt), adapt_nl_err(status));
	status = io_close(&file);
	return (IO_ALL_LINES_SUCCESS);
}
