/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   io_memcpy.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: dkolodze <dkolodze@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/04 19:35:09 by dkolodze      #+#    #+#                 */
/*   Updated: 2023/06/04 21:25:45 by dkolodze      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

void	io_memcpy(void *dst, void *src, int n_bytes)
{
	char	*c_dst;
	char	*c_src;
	int		i;

	c_dst = dst;
	c_src = src;
	i = 0;
	while (i < n_bytes)
	{
		c_dst[i] = c_src[i];
		i += 1;
	}
}
