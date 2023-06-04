/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   io_impl_exit.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: dkolodze <dkolodze@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/04 18:55:36 by dkolodze      #+#    #+#                 */
/*   Updated: 2023/06/04 21:22:43 by dkolodze      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>

#include "codam_io.h"

static char	*s_error_name(int exit_code)
{
	char		*error;

	error = "unknown error; check return code";
	if (exit_code == IO_EXIT_ALLOCATION_ERROR)
		error = "allocation error";
	if (exit_code == IO_EXIT_CLOSE_ERROR)
		error = "close error";
	if (exit_code == IO_EXIT_OPEN_ERROR)
		error = "open error";
	if (exit_code == IO_EXIT_READ_ERROR)
		error = "read error";
	if (exit_code == IO_EXIT_WRITE_ERROR)
		error = "write error";
	if (exit_code == IO_EXIT_WRONG_ARGS_ERROR)
		error = "wrong args error";
	return (error);
}

static void	s_err_write(const char *s)
{
	write(STDERR_FILENO, s, io_signed_strlen(s));
}

void	io_impl_exit(char *func_name, int exit_code)
{
	const char	*magenta_bold = "\033[1m\033[35m";
	const char	*reset = "\033[0m";
	char		*error;

	error = s_error_name(exit_code);
	s_err_write(magenta_bold);
	s_err_write("io:");
	s_err_write(reset);
	s_err_write(" ");
	s_err_write(func_name);
	s_err_write(" exited with ");
	s_err_write(error);
	s_err_write("\n");
	exit(exit_code);
}
