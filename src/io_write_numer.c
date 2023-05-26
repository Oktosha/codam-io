/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   io_write_numer.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: dkolodze <dkolodze@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/26 18:59:22 by dkolodze      #+#    #+#                 */
/*   Updated: 2023/05/26 20:39:43 by dkolodze      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>

#include "codam_io.h"

static int io_write_int_min(int fd)
{
	const char	*int_min_str = "-2147483648";

	return io_write_string(fd, int_min_str);
}

int	io_write_number(int fd, int number)
{
	int retcode;

	if (number == INT_MIN)
		return io_write_int_min(fd);
	if (number < 0)
	{
		if (io_write_char(fd, '-') < 0)
			return (-1);
		number = -number;
	}
	if (number >= 10 && io_write_number(fd, number / 10) < 0)
		return (-1);
	return (io_write_char(fd, (number % 10) + '0'));
}
