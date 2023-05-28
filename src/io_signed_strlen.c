/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   io_signed_strlen.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: dkolodze <dkolodze@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/26 18:48:03 by dkolodze      #+#    #+#                 */
/*   Updated: 2023/05/28 21:08:51 by dkolodze      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "codam_io.h"

int	io_signed_strlen(const char *s)
{
	int	length;

	length = 0;
	while (s[length] != '\0')
	{
		length += 1;
	}
	return (length);
}
