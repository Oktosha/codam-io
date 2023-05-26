/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   io_wrapped_malloc.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: dkolodze <dkolodze@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/26 14:53:44 by dkolodze      #+#    #+#                 */
/*   Updated: 2023/05/26 18:45:48 by dkolodze      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "codam_io.h"

void	*io_wrapped_malloc(int size)
{
	void	*p;

	if (size <= 0)
	{
		io_err("io_wrapped_malloc won't allocate %d memory\n", size);
		exit(IO_EXIT_WRONG_ARGS_ERROR);
	}
	p = malloc(size);
	if (p == NULL && IO_FAILFAST_ON_ALLOCATION_ERROR)
	{
		io_err("io_wrapped_malloc coudn't allocate %d memory\n", size);
		exit(IO_EXIT_ALLOCATION_ERROR);
	}
	return (p);
}
