/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   io_close.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: dkolodze <dkolodze@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/26 21:15:33 by dkolodze      #+#    #+#                 */
/*   Updated: 2023/05/28 21:25:26 by dkolodze      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>

#include "codam_io.h"

t_io_close_status	io_close(t_io_input_file *file)
{
	int					retcode;
	t_io_close_status	status;

	status = IO_CLOSE_SUCCESS;
	retcode = close(file->fd);
	file->fd = -1;
	io_reset_buffer(&(file->buffer));
	if (retcode == -1)
		status = IO_CLOSE_ERROR;
	if (status == IO_CLOSE_ERROR && IO_FAILFAST_ON_CLOSE_ERROR)
		exit(IO_EXIT_CLOSE_ERROR);
	return (status);
}
