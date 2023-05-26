/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   io_open_for_read.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: dkolodze <dkolodze@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/26 20:59:53 by dkolodze      #+#    #+#                 */
/*   Updated: 2023/05/26 21:14:37 by dkolodze      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdlib.h>

#include "codam_io.h"

t_io_open_for_read_status	io_open_for_read( \
	char *filename, \
	t_io_input_file *file)
{
	t_io_open_for_read_status	status;

	io_reset_buffer(&(file->buffer));
	status = IO_OPEN_FOR_READ_SUCCESS;
	file->fd = open(filename, O_RDONLY);
	if (file->fd == -1)
		status = IO_OPEN_FOR_READ_ERROR;
	if (status == IO_OPEN_FOR_READ_ERROR && IO_FAILFAST_ON_OPEN_ERROR)
		exit(IO_EXIT_OPEN_ERROR);
	return (status);
}
