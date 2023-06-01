/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   io_assert.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: dkolodze <dkolodze@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/01 19:44:11 by dkolodze      #+#    #+#                 */
/*   Updated: 2023/06/01 19:54:02 by dkolodze      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <unistd.h>

#include "codam_io.h"

void	io_assert(int condition, const char *fmt, ...)
{
	va_list	ap;
	const char	*red_bold = "\033[1;31m";
	const char	*white_bold = "\033[1;37m";
	const char	*reset = "\033[0m";

	if (condition)
		return ;
	io_err("%sAssertion failed:%s ", red_bold, reset);
	io_err("%s", white_bold);
	va_start(ap, fmt);
	io_vf_print(STDERR_FILENO, fmt, ap);
	va_end(ap);
	io_err("%s\n", reset);
}
