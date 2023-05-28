/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   io_write_string.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: dkolodze <dkolodze@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/26 18:49:57 by dkolodze      #+#    #+#                 */
/*   Updated: 2023/05/28 21:08:34 by dkolodze      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>

#include "codam_io.h"

int	io_write_string(int fd, const char *s)
{
	int	length;
	int	retcode;

	length = io_signed_strlen(s);
	retcode = write(fd, s, length);
	if (retcode < length)
		retcode = -1;
	if (retcode == -1 && IO_FAILFAST_ON_WRITE_ERROR)
		exit(IO_EXIT_WRITE_ERROR);
	return (retcode);
}
