/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   io_write_char.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: dkolodze <dkolodze@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/26 18:56:53 by dkolodze      #+#    #+#                 */
/*   Updated: 2023/05/26 20:31:21 by dkolodze      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>

#include "codam_io.h"

int	io_write_char(int fd, char ch)
{
	int	retcode;

	retcode = write(fd, &ch, 1);
	if (retcode < 1)
		retcode = -1;
	if (retcode == -1 && IO_FAILFAST_ON_WRITE_ERROR)
		exit(IO_EXIT_WRITE_ERROR);
	return (retcode);
}
