/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvan-der <vvan-der@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 13:18:39 by vvan-der          #+#    #+#             */
/*   Updated: 2023/07/06 19:57:05 by vvan-der         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	signal_handler(int signal)
{
	if (signal == SIGUSR1)
		((global->list[global->pos] >> global->i) & 1) = 0;
	else if (signal == SIGUSR2)
}

int	main(void)
{
	ft_putendl_fd(ft_itoa(getpid()), STDOUT_FILENO);
}