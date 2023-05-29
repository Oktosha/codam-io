/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   io_memset.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: dkolodze <dkolodze@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/26 21:06:12 by dkolodze      #+#    #+#                 */
/*   Updated: 2023/05/29 19:21:45 by dkolodze      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "codam_io.h"

void	io_memset(void *memory, int length, char value)
{
	int		i;
	char	*memory_as_char;

	if (length <= 0)
	{
		io_err("Trying to set %d <= 0 bytes of memory to %c\n", length, value);
		exit(IO_EXIT_WRONG_ARGS_ERROR);
	}
	i = 0;
	memory_as_char = memory;
	while (i < length)
	{
		memory_as_char[i] = value;
		i += 1;
	}
}
