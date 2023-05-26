/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   io_out.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: dkolodze <dkolodze@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/26 20:58:11 by dkolodze      #+#    #+#                 */
/*   Updated: 2023/05/26 20:58:40 by dkolodze      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <unistd.h>

#include "codam_io.h"

int	io_out(const char *fmt, ...)
{
	va_list	ap;
	int retcode;

	va_start(ap, fmt);
	retcode = io_vf_print(STDOUT_FILENO, fmt, ap);
	va_end(ap);
	return (retcode);
}
