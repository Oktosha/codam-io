/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   io_err.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: dkolodze <dkolodze@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/26 20:55:33 by dkolodze      #+#    #+#                 */
/*   Updated: 2023/05/28 21:06:48 by dkolodze      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <unistd.h>

#include "codam_io.h"

int	io_err(const char *fmt, ...)
{
	va_list	ap;
	int		retcode;

	va_start(ap, fmt);
	retcode = io_vf_print(STDERR_FILENO, fmt, ap);
	va_end(ap);
	return (retcode);
}
