/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   io_write_string.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: dkolodze <dkolodze@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/26 18:49:57 by dkolodze      #+#    #+#                 */
/*   Updated: 2023/06/04 22:16:57 by dkolodze      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>

#include "codam_io.h"

int	io_write_string(int fd, const char *s)
{
	const char	*msg = "Set IO_PRINT_NULLSTR_NICELY to print NULL with %s\n";
	int			length;
	int			retcode;

	if (s == NULL)
	{
		if (IO_PRINT_NULLSTR_NICELY)
			s = "(null)";
		else
		{
			write(STDERR_FILENO, msg, io_signed_strlen(msg));
			io_impl_exit("io_write_string", IO_EXIT_WRONG_ARGS_ERROR);
		}
	}
	length = io_signed_strlen(s);
	retcode = write(fd, s, length);
	if (retcode < length)
		retcode = -1;
	if (retcode > 0)
		retcode = 0;
	if (retcode == -1 && IO_FAILFAST_ON_WRITE_ERROR)
		io_impl_exit("io_write_string", IO_EXIT_WRITE_ERROR);
	return (0);
}
