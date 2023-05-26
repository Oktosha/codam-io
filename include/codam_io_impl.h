/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   codam_io_impl.h                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: dkolodze <dkolodze@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/26 21:27:25 by dkolodze      #+#    #+#                 */
/*   Updated: 2023/05/26 21:29:43 by dkolodze      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CODAM_IO_IMPL_H
# define CODAM_IO_IMPL_H

typedef struct s_io_impl_string_list {
	char							*data;
	struct s_io_impl_string_list	*next;
}	t_io_impl_string_list;

#endif
