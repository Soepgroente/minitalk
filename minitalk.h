/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minitalk.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvan-der <vvan-der@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/04 13:20:16 by vvan-der      #+#    #+#                 */
/*   Updated: 2023/08/08 17:22:47 by vvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H
# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>
# include <ctype.h>
# include <stdio.h>
# include <sys/types.h>
# include <signal.h>
# include "libft/libft.h"

typedef struct s_data
{
	int		i;
	int		bit;
	char	*msg;
	int		size;
	bool	ready_to_send;
	char	c;
}	t_data;

#endif