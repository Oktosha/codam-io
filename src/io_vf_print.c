/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   io_vf_print.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: dkolodze <dkolodze@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/26 20:40:11 by dkolodze      #+#    #+#                 */
/*   Updated: 2023/05/26 20:55:22 by dkolodze      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>

#include "codam_io.h"

static void exit_wrong_format(int fd, const char *fmt, int pos)
{
	io_err("in io_vf_print(%d, \"%s\", ...)\n", fd, fmt);
	io_err("Error: wrong format at position %d\n", pos);
	exit(IO_EXIT_WRONG_ARGS_ERROR);
}

int	io_vf_print(int fd, const char *fmt, va_list ap)
{
	int	pos;
	int retcode;

	pos = 0;
	retcode = 0;
	while (fmt[pos] != '\0' && retcode == 0)
	{
		if (fmt[pos] == '%')
		{
			if (fmt[pos + 1] == 's')
				retcode = io_write_string(fd, va_arg(ap, char *));
			else if (fmt[pos + 1] == 'c')
				retcode = io_write_char(fd, va_arg(ap, int));
			else if (fmt[pos + 1] == 'd')
				retcode = io_write_number(fd, va_arg(ap, int));
			else
				exit_wrong_format(fd, fmt, pos);
			pos += 2;
		}
		else
			retcode = io_write_char(fd, fmt[pos++]);
	}
	return (retcode);
}
