/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   io_is_ascii_print.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: dkolodze <dkolodze@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/09 14:25:22 by dkolodze      #+#    #+#                 */
/*   Updated: 2023/06/09 14:26:51 by dkolodze      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "codam_io.h"

int	io_is_ascii_print(int ch)
{
	return ((ch >= ' ') && (ch <= '~'));
}
