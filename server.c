/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   server.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvan-der <vvan-der@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/04 13:18:39 by vvan-der      #+#    #+#                 */
/*   Updated: 2023/07/28 13:02:18 by vvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	signal_handler(int signal)
{
}

int	main(void)
{
	int	i;

	i = 0;
	if (ft_printf("%d\n", getpid()) == 1)
		return (1);
}