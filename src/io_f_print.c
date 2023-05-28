/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   io_f_print.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: dkolodze <dkolodze@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/26 20:58:53 by dkolodze      #+#    #+#                 */
/*   Updated: 2023/05/28 21:07:20 by dkolodze      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <unistd.h>

#include "codam_io.h"

int	io_f_print(int fd, const char *fmt, ...)
{
	va_list	ap;
	int		retcode;

	va_start(ap, fmt);
	retcode = io_vf_print(fd, fmt, ap);
	va_end(ap);
	return (retcode);
}
