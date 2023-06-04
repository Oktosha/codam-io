/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   io_read_file.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: dkolodze <dkolodze@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/04 18:18:17 by dkolodze      #+#    #+#                 */
/*   Updated: 2023/06/04 21:30:24 by dkolodze      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

#include "codam_io.h"

static t_io_read_file_status	s_handle_open_error(char *filename)
{
	if (IO_FAILFAST_ON_OPEN_ERROR)
	{
		io_err("couldn't open file %s\n", filename);
		io_impl_exit("io_read_file", IO_EXIT_OPEN_ERROR);
	}
	return (IO_READ_FILE_OPEN_ERROR);
}

static void	s_handle_close_error(t_io_read_file_status *status, \
	int fd, char *filename)
{
	if (IO_FAILFAST_ON_CLOSE_ERROR)
	{
		io_err("error closing %d assosiated with %s\n", fd, filename);
		if (*status != IO_READ_FILE_SUCCESS)
			io_err("also status was %d (unsuccessful)\n", *status);
		io_impl_exit("io_read_file", IO_EXIT_CLOSE_ERROR);
	}
	*status = *status | IO_READ_FILE_CLOSE_ERROR;
}

static t_io_read_file_status	s_cleanup( \
	t_io_read_file_status status, t_io_charz *data, int fd, \
	char *filename)
{
	int	close_status;

	close_status = close(fd);
	if (status == IO_READ_FILE_SUCCESS && close_status == 0)
		return (IO_READ_FILE_SUCCESS);
	free(data->data);
	data->data = NULL;
	data->capacity = 0;
	data->len = 0;
	if (close_status == -1)
		s_handle_close_error(&status, fd, filename);
	if ((status & IO_READ_FILE_ALLOC_ERROR) && IO_FAILFAST_ON_ALLOCATION_ERROR)
	{
		io_err("can't allocate memory after reading %d bytes", data->len);
		io_err(" from %s\n", filename);
		io_impl_exit("io_read_file", IO_EXIT_ALLOCATION_ERROR);
	}
	if ((status & IO_READ_FILE_READ_ERROR) && IO_FAILFAST_ON_READ_ERROR)
	{
		io_err("error reading %s after %d bytes\n", filename, data->len);
		io_impl_exit("io_read_file", IO_EXIT_READ_ERROR);
	}
	return (status);
}

static int	s_inc_capacity(t_io_charz *data, int minimum_space_to_add)
{
	int		new_capacity;
	char	*new_data;

	new_capacity = data->len + minimum_space_to_add;
	if (data->len * 2 > new_capacity)
		new_capacity = data->len * 2;
	if (new_capacity < 4)
		new_capacity = 4;
	new_data = io_wrapped_malloc(new_capacity);
	if (new_data == NULL)
		return (-1);
	if (data->data != NULL && data->len > 0)
		io_memcpy(new_data, data->data, data->len);
	free(data->data);
	data->data = new_data;
	data->capacity = new_capacity;
	return (0);
}

t_io_read_file_status	io_read_file(char *filename, t_io_charz *data)
{
	char	buffer[IO_BUFFER_SIZE];
	int		n;
	int		fd;

	data->capacity = 0;
	data->len = 0;
	data->data = NULL;
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (s_handle_open_error(filename));
	n = read(fd, buffer, IO_BUFFER_SIZE);
	while (n > 0)
	{
		if (data->len + n > data->capacity && s_inc_capacity(data, n) == -1)
			return (s_cleanup(IO_READ_FILE_ALLOC_ERROR, data, fd, filename));
		io_memcpy(data->data + data->len, buffer, n);
		data->len += n;
		n = read(fd, buffer, IO_BUFFER_SIZE);
	}
	if (n < 0)
		return (s_cleanup(IO_READ_FILE_READ_ERROR, data, fd, filename));
	return (s_cleanup(IO_READ_FILE_SUCCESS, data, fd, filename));
}
