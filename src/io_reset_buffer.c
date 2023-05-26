/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   io_reset_buffer.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: dkolodze <dkolodze@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/26 21:11:31 by dkolodze      #+#    #+#                 */
/*   Updated: 2023/05/26 21:34:01 by dkolodze      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "codam_io.h"

void	io_reset_buffer(t_io_buffer *buffer)
{
	io_memset(buffer->data, IO_BUFFER_SIZE, 0);
	buffer->start = 0;
	buffer->len = 0;
}
